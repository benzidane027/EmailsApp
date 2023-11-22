#include "customwidget.h"

// setContentsMargins(int left, int top, int right, int bottom)

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

mQWidgetMessage::mQWidgetMessage(std::string senderMail, std::string Messagesubject, std::string senderImage, std::string senderDate,std::string MessageBody, QWidget *parent) : QWidget(parent)
{

    this->senderImage=senderImage;
    this->senderMail=senderMail;
    this->Messagesubject=Messagesubject;
    this->senderDate=senderDate;

   // this->MessageBody= &MessageBody;


    setObjectName("mesageHeaderTemplate");
    setStyleSheet("#mesageHeaderTemplate {border-bottom:1.5px solid rgba(127,127,127,0.3);}\n\
                    #mesageHeaderTemplate:hover { background-color: rgba(220,224,230,0.3);   border-radius: 5px; } \n\
                    ");

    setMinimumHeight(90);
    setMaximumHeight(100);
    setCursor(Qt::PointingHandCursor);
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
    userNameLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *userNameLable = new QLabel();

    userNameLable->setText(QString::fromStdString(senderMail));
    // userNameLable->setMaximumWidth(200);
    // userNameLable->setMinimumWidth(200);

    userNameLable->setStyleSheet("border:none;color:rgba(0,0,0,0.8);font-size:16px;");
    userNameLayout->setContentsMargins(5, 5, 0, 0);
    userNameLayout->setAlignment(Qt::AlignTop);
    userNameLayout->addWidget(userNameLable);

    QWidget *userDateWidget = new QWidget();
    QLabel *userDateLable = new QLabel(userDateWidget);
    userDateLable->setText(QString::fromStdString(senderDate));
    userDateLable->setStyleSheet("border:none;color:rgba(0,0,0,0.5);font-size:17px;");

    userDateWidget->setMaximumWidth(40);
    userDateWidget->setMinimumWidth(40);

    // userPictureWidget->setStyleSheet("background-color:yellow");

    // userNameWidget->setStyleSheet("background-color:pink");
    // userDateWidget->setStyleSheet("background-color:grey");

    subTopMainLayout->addWidget(userPictureWidget);
    subTopMainLayout->addWidget(userNameWidget);
    subTopMainLayout->addWidget(userDateWidget);

    QWidget *buttomOfMainLayout = new QWidget();
    buttomOfMainLayout->setMaximumWidth(280);
    buttomOfMainLayout->setMinimumWidth(280);

    QHBoxLayout *subButtomMainLayout = new QHBoxLayout(buttomOfMainLayout);
    subButtomMainLayout->setContentsMargins(0, 0, 0, 0);
    subButtomMainLayout->setSpacing(0);
    QLabel *messageDescribtionLabel = new QLabel();
    messageDescribtionLabel->setText(QString::fromStdString(Messagesubject));

    messageDescribtionLabel->setWordWrap(true);

    subButtomMainLayout->addWidget(messageDescribtionLabel);

    // messageDescribtionLabel->setStyleSheet("background-color:green;color:rgba(0,0,0,0.7);");

    topOfMainLayout->setStyleSheet("border:none;");
    buttomOfMainLayout->setStyleSheet("border:none;");

    mainLayout->addWidget(topOfMainLayout);
    mainLayout->addWidget(buttomOfMainLayout);

    // setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    // setLayout(new QVBoxLayout(parent));
    // setGeometry(QRect(0, 0, 10, 10));
    // resize(QSize(10,10));
}
