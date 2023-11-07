#include "customwidget.h"

//setContentsMargins(int left, int top, int right, int bottom)

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
    setMinimumHeight(90);
    setMaximumHeight(100);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    QWidget *topOfMainLayout = new QWidget();

    QHBoxLayout *subTopMainLayout = new QHBoxLayout(topOfMainLayout);
    subTopMainLayout->setContentsMargins(0, 0, 0, 0);
    subTopMainLayout->setSpacing(0);

    QWidget *userPictureWidget = new QWidget();
    userPictureWidget->setMinimumWidth(45);
    userPictureWidget->setMaximumWidth(45);
    QHBoxLayout *userPictureLayout = new QHBoxLayout(userPictureWidget);

    QLabel *userPictureLabel = new QLabel();
    userPictureLayout->addWidget(userPictureLabel);

    userPictureLayout->setContentsMargins(4, 2, 2, 4);
    userPictureLabel->setStyleSheet("background-color:rgba(0,0,0,0.1); border-radius: 19px;");


    QWidget *userNameWidget = new QWidget();
    QHBoxLayout *userNameLayout = new QHBoxLayout(userNameWidget);
    userNameLayout->setContentsMargins(0,0,0,0);
    QLabel *userNameLable = new QLabel();

    userNameLable->setText("Amine benzidane");
    userNameLable->setStyleSheet("border:none;color:rgba(0,0,0,0.8);font-size:16px;");
    userNameLayout->setContentsMargins(5,5,0,0);
    userNameLayout->setAlignment(Qt::AlignTop);
    userNameLayout->addWidget(userNameLable);

    QWidget *userDateWidget = new QWidget();
    userDateWidget->setMinimumWidth(50);
    userDateWidget->setMaximumWidth(50);
    QLabel *userDateLable = new QLabel(userDateWidget);
    userDateLable->setText("8 Oct");
    userDateLable->setStyleSheet("border:none;color:rgba(0,0,0,0.5);font-size:17px;");

    //userPictureWidget->setStyleSheet("background-color:yellow");

    // userNameWidget->setStyleSheet("background-color:pink");
    // userDateWidget->setStyleSheet("background-color:grey");

    subTopMainLayout->addWidget(userPictureWidget);
    subTopMainLayout->addWidget(userNameWidget);
    subTopMainLayout->addWidget(userDateWidget);

    QWidget *buttomOfMainLayout = new QWidget();
    QHBoxLayout *subButtomMainLayout = new QHBoxLayout(buttomOfMainLayout);
    subButtomMainLayout->setContentsMargins(0, 0, 0, 0);
    subButtomMainLayout->setSpacing(0);
    QLabel *messageDescribtionLabel = new QLabel();
    messageDescribtionLabel->setText("hello this is test message just fir example");
    messageDescribtionLabel->setWordWrap(true);
    subButtomMainLayout->addWidget(messageDescribtionLabel);

    //messageDescribtionLabel->setStyleSheet("background-color:green;color:rgba(0,0,0,0.7);");



    topOfMainLayout->setStyleSheet("border:none;");
    buttomOfMainLayout->setStyleSheet("border:none;");

    mainLayout->addWidget(topOfMainLayout);
    mainLayout->addWidget(buttomOfMainLayout);

    // setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    // setLayout(new QVBoxLayout(parent));
    // setGeometry(QRect(0, 0, 10, 10));
    // resize(QSize(10,10));
}
