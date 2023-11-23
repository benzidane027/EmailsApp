#ifndef QCUSTOMWIDGET_H
#define QCUSTOMWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QString>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <vmime/vmime.hpp>
#include "../loadingWidget/waitingspinnerwidget.h"

#include "../model/mailhandler.h"
#include "../model/model.h"

class mQLable : public QLabel
{
private:
    bool stack_has_been_set = false;

public:
    QStackedWidget *stk;
    mQLable(QWidget *parent = nullptr);
    void setStack(QStackedWidget *_stk = nullptr)
    {
        this->stk = _stk;
        stack_has_been_set = true;
    }

protected:
    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (stack_has_been_set)
            stk->setCurrentIndex(1);
    }
};

class mQWidgetMessage : public QWidget
{
private:
    std::string UID;

    std::string senderImage;
    std::string senderMail;
    std::string Messagesubject;
    std::string senderDate;
    std::shared_ptr<vmime::component> MessageBody;
    std::string MessageType;

    bool stack_has_been_set = false;
    QStackedWidget *stk;

    QWidget *loadingPage;
    QLabel *userImageTemplate;
    QLabel *userNameTemplate;
    QLabel *emailsTemplate;
    QLabel *subjectTemplate;
    QTextBrowser *bodyTemplate;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override
    {
        qDeleteAll(loadingPage->findChildren<WaitingSpinnerWidget *>());
        stk->setCurrentIndex(1);

        WaitingSpinnerWidget *spinner = new WaitingSpinnerWidget(loadingPage);

        spinner->setRoundness(70.0);
        spinner->setMinimumTrailOpacity(15.0);
        spinner->setTrailFadePercentage(70.0);
        spinner->setNumberOfLines(12);
        spinner->setLineLength(10);
        spinner->setLineWidth(5);
        spinner->setInnerRadius(10);
        spinner->setRevolutionsPerSecond(1);
        spinner->setColor(QColor(87, 91, 97));
        spinner->start();

        fetchMailThread *th = new fetchMailThread(UID);
        th->start();

       connect(th, &fetchMailThread::workFinished, this, [&](QList<QMap<std::string, std::string>> resualt)
               {

                 stk->setCurrentIndex(0);
                // QVBoxLayout *lay = new QVBoxLayout(ui->widget_49);

                // for (QMap<std::string, std::string> msg : resualt)
                // {
                //     qDebug()<<msg.value("id").c_str();
                //     mQWidgetMessage *p = new mQWidgetMessage(msg.value("UID"),msg.value("senderMail"), msg.value("Messagesubject"), "", msg.value("senderDate"),"msg_body");
                //     p->TemplateDetails(ui->widget_52,ui->stackedWidget_3,ui->label_32,ui->label_33,ui->label_34,ui->label_35,ui->textBrowser);
                //     lay->addWidget(p);

                // }
               qDebug() << "###done###";

               });

        this->subjectTemplate->setText(QString::fromStdString(this->Messagesubject));
        this->emailsTemplate->setText(QString::fromStdString(this->senderMail));
    }

public:
    mQWidgetMessage(std::string UID, std::string senderMail, std::string Messagesubject, std::string senderImage, std::string senderDate, std::string MessageBody, QWidget *parent = nullptr);
    void TemplateDetails(QWidget *loadingPage, QStackedWidget *_stk, QLabel *userImageTemplate, QLabel *userNameTemplate, QLabel *emailsTemplate, QLabel *subjectTemplate, QTextBrowser *bodyTemplate)
    {
        this->stk = _stk;
        this->loadingPage = loadingPage;
        this->userImageTemplate = userImageTemplate;
        this->userNameTemplate = userNameTemplate;
        this->emailsTemplate = emailsTemplate;
        this->subjectTemplate = subjectTemplate;
        this->bodyTemplate = bodyTemplate;
        stack_has_been_set = true;

        fetchMailThread *th = new fetchMailThread("");
    }
};

#endif // QCUSTOM_H
