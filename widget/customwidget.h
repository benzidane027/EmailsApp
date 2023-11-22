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


// #include <QtWaitingSpinner>
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
        this->subjectTemplate->setText(QString::fromStdString(this->Messagesubject));
        this->emailsTemplate->setText(QString::fromStdString(this->senderMail));
    }

public:
    mQWidgetMessage(std::string senderMail, std::string Messagesubject, std::string senderImage, std::string senderDate, std::string MessageBody, QWidget *parent = nullptr);
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
    }
};

#endif // QCUSTOM_H
