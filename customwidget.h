#ifndef QCUSTOMWIDGET_H
#define QCUSTOMWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QString>
#include <QStackedWidget>
#include <QVBoxLayout>

//#include <QtWaitingSpinner>
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

public:

    mQWidgetMessage(QWidget *parent = nullptr);


};

#endif // QCUSTOM_H
