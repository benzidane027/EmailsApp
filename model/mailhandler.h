#ifndef QCUSTOM_H
#define QCUSTOM_H

#include <QThread>
#include <QDebug>
#include <QVBoxLayout>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>
#include "../ENV.h"
#include <boost/algorithm/string.hpp>
#include <regex>

QT_BEGIN_NAMESPACE
namespace Mail
{
    class sendMailThread;
    class getMailsThread;
    class fetchMailThread;

}
QT_END_NAMESPACE

class sendMailThread : public QThread
{
    Q_OBJECT

private:
    vmime::string reciverMail;
    vmime::string subjectMessage;
    vmime::string contentMessage;
    bool isInit = false;

public:
    sendMailThread(QObject *parent = nullptr)
        : QThread(parent)
    {
    }
    void initMailThread(vmime::string reciverMail, vmime::string subjectMessage, vmime::string contentMessage)
    {
        this->reciverMail = reciverMail;
        this->subjectMessage = subjectMessage;
        this->contentMessage = contentMessage;
        this->isInit = true;
    }
    vmime::string &str()
    {
        // for testing
        static vmime::string str;
        str.append(this->reciverMail);
        str.append(" || ");
        str.append(this->subjectMessage);
        str.append("||");
        str.append(this->contentMessage);

        return str;
    }

protected:
    void run() override
    {
        if (not this->isInit)
        {
            qDebug() << "not init yet";
            return;
        }

        qDebug() << "start sending **********";

        vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
        // vmime::shared_ptr<vmime::mailbox> mbox1 = vmime::make_shared<vmime::mailbox>(vmime::text("John Doe"), "john.doe@acme.com");
        vmime::shared_ptr<vmime::message> msg = vmime::make_shared<vmime::message>();

        vmime::shared_ptr<vmime::body> bdy = msg->getBody();
        vmime::shared_ptr<vmime::header> hdr = msg->getHeader();

        vmime::shared_ptr<vmime::headerFieldFactory> hfFactory = vmime::headerFieldFactory::getInstance();

        // append date
        vmime::shared_ptr<vmime::headerField> dateField = hfFactory->create(vmime::fields::DATE);
        dateField->setValue(vmime::datetime::now());
        hdr->appendField(dateField);

        // Append a Subject :field
        vmime::shared_ptr<vmime::headerField> subjectField = hfFactory->create(vmime::fields::SUBJECT);
        subjectField->setValue(this->subjectMessage);
        hdr->appendField(subjectField);

        // Append a From: field
        vmime::shared_ptr<vmime::headerField> fromField = hfFactory->create(vmime::fields::FROM);
        fromField->setValue(vmime::make_shared<vmime::mailbox>(Env::CONFIG_EMIAL));
        hdr->appendField(fromField);

        // Append a To: field
        vmime::shared_ptr<vmime::headerField> toField = hfFactory->create(vmime::fields::TO);
        vmime::shared_ptr<vmime::addressList> recipients = vmime::make_shared<vmime::addressList>();
        recipients->appendAddress(vmime::make_shared<vmime::mailbox>(this->reciverMail));
        // recipients->appendAddress(vmime::make_shared<vmime::mailbox>("toTwo@mail.org")) ;
        // recipients->appendAddress(vmime::make_shared<vmime::mailbox>("toThree@mail.org")) ;

        toField->setValue(recipients);

        hdr->appendField(toField);

        // append message body content
        bdy->setContents(vmime::make_shared<vmime::stringContentHandler>(this->contentMessage));

        // create session
        vmime::shared_ptr<vmime::net::session> theSession = vmime::net::session::create();
        vmime::utility::url url("smtp://" + vmime::string(Env::CONFIG_HOST));

        vmime::shared_ptr<vmime::net::transport> tr = theSession->getTransport(url);

        tr->setProperty("options.need-authentication", true);
        tr->setProperty("auth.username", Env::CONFIG_EMIAL);
        tr->setProperty("auth.password", Env::CONFIG_PASSWORD);
        tr->connect();
        tr->send(msg);

        qDebug() << "end sending **********";
    }
};


class getMailsThread : public QThread
{
    Q_OBJECT

signals:
    void workFinished(QList<QMap<std::string, std::string>>);

public:
    getMailsThread(QWidget *parent = nullptr)
        : QThread(parent)
    {
    }

    vmime::string &str()
    {
        static vmime::string str;

        return str;
    }

protected:
    void run() override
    {
        QList<QMap<std::string, std::string>> data;
        std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

        qDebug() << "start geting **********";
        try
        {
            QMap<std::string, std::string> dataLine;

            vmime::shared_ptr<vmime::net::session> theSession = vmime::net::session::create();
            vmime::utility::url url("imap://" + vmime::string(Env::CONFIG_HOST));

            vmime::shared_ptr<vmime::net::store> st = theSession->getStore(url);

            st->setProperty("options.need-authentication", true);
            st->setProperty("auth.username", Env::CONFIG_EMIAL);
            st->setProperty("auth.password", Env::CONFIG_PASSWORD);
            st->connect();

            vmime::net::folder::path path;
            path.appendComponent(vmime::net::folder::path::component("INBOX"));

            vmime::shared_ptr<vmime::net::folder> fld = st->getFolder(path);
            fld->open(vmime::net::folder::MODE_READ_WRITE);
            int messageCount = fld->getMessageCount();

            std::vector<std::shared_ptr<vmime::net::message>> allMessages = fld->getMessages(vmime::net::messageSet::byNumber(messageCount -10 , messageCount));
            fld->fetchMessages(allMessages, vmime::net::fetchAttributes::ENVELOPE);

            std::reverse(allMessages.begin(), allMessages.end());
            for (auto msg : allMessages)
            {

                std::string senderMail = msg->getHeader()->From()->getValue()->generate().c_str();
                std::sregex_iterator emailIterator(senderMail.begin(), senderMail.end(), emailRegex);
                std::sregex_iterator endIterator;

                while (emailIterator != endIterator)
                {
                    std::smatch match = *emailIterator;
                    senderMail = match.str();
                    boost::trim(senderMail);
                    ++emailIterator;
                }
                vmime::string senderMessagesubject = msg->getHeader()->Subject()->getValue()->generate().c_str();

                vmime::text senderMessagesubjectoutText;
                vmime::text::decodeAndUnfold(senderMessagesubject, &senderMessagesubjectoutText);

                dataLine.insert("UID", msg->getUID());
                dataLine.insert("senderImage", "");
                dataLine.insert("senderMail", senderMail);
                dataLine.insert("Messagesubject", senderMessagesubjectoutText.getConvertedText(vmime::charset("utf-8")));
                dataLine.insert("senderDate", "8 Oct");
                data.append(dataLine);

            }
            emit workFinished(data);
        }
        catch (...)
        {
            qDebug() << "Error while fetching try agian";
            run();
        }
    }
};

class fetchMailThread : public QThread
{
    Q_OBJECT

signals:
    void workFinished(QList<QMap<std::string, std::string>>);
private:
    std::string msgUID;

public:
    fetchMailThread(std::string msgUID,QWidget *parent = nullptr)
        : QThread(parent)
    {
        this->msgUID = msgUID;
    }

    vmime::string &str()
    {
        static vmime::string str;

        return str;
    }

protected:
    void run() override
    {
        QList<QMap<std::string, std::string>> data;
        std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

        qDebug() << "start geting **********";
        try
        {
            QMap<std::string, std::string> dataLine;

            // vmime::shared_ptr<vmime::net::session> theSession = vmime::net::session::create();
            // vmime::utility::url url("imap://" + vmime::string(Env::CONFIG_HOST));

            // vmime::shared_ptr<vmime::net::store> st = theSession->getStore(url);

            // st->setProperty("options.need-authentication", true);
            // st->setProperty("auth.username", Env::CONFIG_EMIAL);
            // st->setProperty("auth.password", Env::CONFIG_PASSWORD);
            // st->connect();

            // vmime::net::folder::path path;
            // path.appendComponent(vmime::net::folder::path::component("INBOX"));

            // vmime::shared_ptr<vmime::net::folder> fld = st->getFolder(path);
            // fld->open(vmime::net::folder::MODE_READ_WRITE);
            // int messageCount = fld->getMessageCount();

            // std::vector<std::shared_ptr<vmime::net::message>> allMessages = fld->getMessages(vmime::net::messageSet::byUID(this->msgUID));
            // fld->fetchMessages(allMessages, vmime::net::fetchAttributes::ENVELOPE);

            // // msg->getHeader()->hasField("to")
            // // msg->getParsedMessage()->getBody()->getContentType().generate();

            // std::reverse(allMessages.begin(), allMessages.end());
            // for (auto msg : allMessages)
            // {

            //     fld->fetchMessage(msg, vmime::net::fetchAttributes::STRUCTURE);

            //     vmime::utility::outputStreamAdapter out(std::cout);
            //     vmime::messageParser parser(msg->getParsedMessage());
            //     for (size_t i = 0; i < parser.getTextPartCount(); i++)
            //     {
            //          const vmime::textPart &part = *parser.getTextPartAt(i);
            //         // qDebug() << "\n######\n" << part.getType().generate() << "\n######\n";
            //          qDebug() <<"";
            //         const vmime::textPart &tp = dynamic_cast<const vmime::textPart &>(part);
            //         tp.getText()->generate(out,msg->getParsedMessage()->getBody()->getEncoding());
            //         if (part.getType().getSubType() == vmime::mediaTypes::TEXT_HTML)
            //         {

            //             part.getText().get()->generate(out, msg->getParsedMessage()->getBody()->getEncoding());
            //         }
            //         else
            //         {
            //             //const vmime::textPart &tp = dynamic_cast<const vmime::textPart &>(part);
            //             //tp.getText()->generate(out,msg->getParsedMessage()->getBody()->getEncoding());
            //         }
            //     }


            //     std::string senderMail = msg->getHeader()->From()->getValue()->generate().c_str();
            //     std::sregex_iterator emailIterator(senderMail.begin(), senderMail.end(), emailRegex);
            //     std::sregex_iterator endIterator;

            //     while (emailIterator != endIterator)
            //     {
            //         std::smatch match = *emailIterator;
            //         senderMail = match.str();
            //         boost::trim(senderMail);
            //         ++emailIterator;
            //     }
            //     vmime::string senderMessagesubject = msg->getHeader()->Subject()->getValue()->generate().c_str();
            //     // boost::trim(senderMessagesubject);

            //     vmime::text senderMessagesubjectoutText;
            //     vmime::text::decodeAndUnfold(senderMessagesubject, &senderMessagesubjectoutText);

            //     dataLine.insert("id", "");
            //     dataLine.insert("senderImage", "");
            //     dataLine.insert("senderMail", senderMail);
            //     dataLine.insert("Messagesubject", senderMessagesubjectoutText.getConvertedText(vmime::charset("utf-8")));
            //     dataLine.insert("senderDate", "8 Oct");
            //     dataLine.insert("MessageBody", "");
            //     dataLine.insert("MessageType", "");
            //     data.append(dataLine);
            //     //  qDebug()<<"fetded"<<msg->getParsedMessage
            //     // vmime_msg_test = msg->getHeader()->generate();

            //     // std::shared_ptr<vmime::contentHandler> obj = msg->getParsedMessage()->getBody()->getContents()->clone();

            //     // qDebug() << msg->getHeader()->To()->getValue()->generate();
            //     //     vmime::utility::outputStreamAdapter out(std::cout);
            //     //     // obj->generate(out,msg->getParsedMessage()->getBody()->getEncoding());
            //     //     vmime::messageParser parser(msg->getParsedMessage());
            //     //     for (size_t i = 0; i < parser.getTextPartCount(); i++)
            //     //     {
            //     //         const vmime::textPart &part = *parser.getTextPartAt(i);
            //     //        // qDebug() << "\n######\n" << part.getType().generate() << "\n######\n";

            //     //         if (part.getType().getSubType() == vmime::mediaTypes::TEXT_HTML)
            //     //         {

            //     //             part.getText().get()->generate(out,msg->getParsedMessage()->getBody()->getEncoding());
            //     //         }
            //     //         else
            //     //         {
            //     //             //const vmime::textPart &tp = dynamic_cast<const vmime::textPart &>(part);
            //     //             //tp.getText()->generate(out,msg->getParsedMessage()->getBody()->getEncoding());
            //     //         }
            //     //     }
            //     //  qDebug()<< msg->getNumber();
            //     //    std::vector<std::shared_ptr<vmime::bodyPart>> bodyParts= msg->getParsedMessage()->getBody()->getPartList();
            //     //    for (auto bodyPart: bodyParts){
            //     //      qDebug()<< "\n############  start ##################\n";
            //     //      qDebug()<<bodyPart->generate();
            //     //      qDebug()<< "\n############  done ##################\n";
            //     //    }
            // }
            emit workFinished(data);
        }
        catch (...)
        {

            qDebug() << "Error while fetching try agian";
            run();
        }
    }
};

#endif



