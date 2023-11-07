#include "customwidget.h"

mQLable::mQLable(QWidget *parent) : QLabel(parent)
{
    setText("singup");
    setStyleSheet(
        "border-bottom-width: 1px;\
        border-bottom-style: solid;\
        border-radius: 0px;\
        border-bottom-color:#0074d9;\
        color: #0074d9; \
        ");
}

mQWidgetMessage::mQWidgetMessage(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("border-bottom:1.5px solid rgba(127,127,127,0.3);");
    setMinimumHeight(80);
    setMaximumHeight(100);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    QWidget *topOfMainLayout=new QWidget();

    QHBoxLayout *subTopMainLayout = new QHBoxLayout(topOfMainLayout);
    subTopMainLayout->setContentsMargins(0,0,0,0);
    subTopMainLayout->setSpacing(0);

    QWidget *userPictureWidget=new QWidget();
    userPictureWidget->setMinimumWidth(45);
    userPictureWidget->setMaximumWidth(45);

    QWidget *userNameWidget=new QWidget();
    QLabel *userNameLable=new QLabel(userNameWidget);
    userNameLable->setText(" Amine benzidane");
    userNameLable->setStyleSheet("border:none;color:rgba(0,0,0,0.8);font-size:16px;");

    QWidget *userDateWidget=new QWidget();
    userDateWidget->setMinimumWidth(50);
    userDateWidget->setMaximumWidth(50);
    QLabel *userDateLable=new QLabel(userDateWidget);
    userDateLable->setText("8 Oct");
    userDateLable->setStyleSheet("border:none;color:rgba(0,0,0,0.5);font-size:17px;");

    userPictureWidget->setStyleSheet("background-color:yellow");
    //userNameWidget->setStyleSheet("background-color:pink");
    //userDateWidget->setStyleSheet("background-color:grey");

    subTopMainLayout->addWidget(userPictureWidget);
    subTopMainLayout->addWidget(userNameWidget);
    subTopMainLayout->addWidget(userDateWidget);

    QWidget *buttomOfMainLayout=new QWidget();

    //topOfMainLayout->setStyleSheet("background-color:red;border:none;");
    buttomOfMainLayout->setStyleSheet("background-color:green;border:none;");

    mainLayout->addWidget(topOfMainLayout);
    mainLayout->addWidget(buttomOfMainLayout);

    // setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    // setLayout(new QVBoxLayout(parent));
    // setGeometry(QRect(0, 0, 10, 10));
    // resize(QSize(10,10));
}
