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
    char *c_str()
    {
        // for testing
        char *resualt;
        strcat(resualt, this->reciverMail.c_str());
        strcat(resualt, this->subjectMessage.c_str());
        strcat(resualt, this->contentMessage.c_str());

        return resualt;
    }

protected:
    void run() override
    {
        if (not this->isInit){
            qDebug() << "not init yet";
             return;
        }
           

        qDebug() << "start sending **********";

        vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
        vmime::shared_ptr<vmime::mailbox> mbox1 = vmime::make_shared<vmime::mailbox>(vmime::text("John Doe"), "john.doe@acme.com");
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
        subjectField->setValue(vmime::text("Message subject s"));
        hdr->appendField(subjectField);

        // Append a From: field
        vmime::shared_ptr<vmime::headerField> fromField = hfFactory->create(vmime::fields::FROM);
        fromField->setValue(vmime::make_shared<vmime::mailbox>(Env::CONFIG_EMIAL));
        hdr->appendField(fromField);

        // Append a To: field
        vmime::shared_ptr<vmime::headerField> toField = hfFactory->create(vmime::fields::TO);
        vmime::shared_ptr<vmime::addressList> recipients = vmime::make_shared<vmime::addressList>();
        recipients->appendAddress(vmime::make_shared<vmime::mailbox>("benzidane27@gmail.com"));
        // recipients->appendAddress(vmime::make_shared<vmime::mailbox>("toTwo@mail.org")) ;
        // recipients->appendAddress(vmime::make_shared<vmime::mailbox>("toThree@mail.org")) ;

        toField->setValue(recipients);

        hdr->appendField(toField);

        // append message body content
        bdy->setContents(vmime::make_shared<vmime::stringContentHandler>("This i s the text of your message"));

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

#endif