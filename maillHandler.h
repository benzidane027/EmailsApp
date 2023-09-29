#ifndef QCUSTOM_H
#define QCUSTOM_H

#include <QThread>
#include <QDebug>

#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>

#include "ENV.h"

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

class getMailThread : public QThread
{
    Q_OBJECT

public:
    getMailThread(QObject *parent = nullptr)
        : QThread(parent)
    {
    }
    void initMailThread(vmime::string reciverMail, vmime::string subjectMessage, vmime::string contentMessage)
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

        qDebug() << "start geting **********";
        vmime::shared_ptr<vmime::net::session> theSession = vmime::net::session::create();
        vmime::utility::url url("imap://" + vmime::string(Env::CONFIG_HOST));

        vmime::shared_ptr<vmime::net::store> st = theSession->getStore(url);
         st->getInfos();

        st->setProperty("options.need-authentication", true);
        st->setProperty("auth.username", Env::CONFIG_EMIAL);
        st->setProperty("auth.password", Env::CONFIG_PASSWORD);
        st->connect();

        vmime::net::folder::path path;
        path.appendComponent(vmime::net::folder::path::component("INBOX"));
        vmime::shared_ptr<vmime::net::folder> fld = st->getFolder(path);
        fld->open(vmime::net::folder::MODE_READ_WRITE);

        std::vector<std::shared_ptr<vmime::net::message>> allMessages = fld->getMessages(vmime::net::messageSet::byNumber(162, 162));
        fld->fetchMessages(allMessages, vmime::net::fetchAttributes::FLAGS | vmime::net::fetchAttributes::ENVELOPE);
        // msg->getHeader()->hasField("to")
        //msg->getParsedMessage()->getBody()->getContentType().generate();
        //msg->getParsedMessage()->getBody()->getEncoding().generate()
        for (auto msg : allMessages)
        {        
            fld->fetchMessage(msg, vmime::net::fetchAttributes::STRUCTURE);
            std::shared_ptr<vmime::contentHandler> obj = msg->getParsedMessage()->getBody()->getContents()->clone();
            //vmime::utility::outputStream* os;
            
             vmime::encoding utf=obj->getEncoding();
            //obj->generate(os,utf);

        }
        qDebug() << "end geting **********";
    }
};

#endif