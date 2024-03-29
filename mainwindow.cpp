#include "mainwindow.h"


std::string Email_str;
std::string Pass_str;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    qDebug() << "start ***";
    ui->setupUi(this);
    this->setWindowTitle("Welcome");
    // this->ui->pushButton_3->hide();

    mQLable *custom = new mQLable(this->ui->widget_10);
    QCursor cursor;
    cursor.setShape(Qt::CursorShape::PointingHandCursor);
    custom->setCursor(cursor);
    custom->setStack(this->ui->stackedWidget);
    custom->setGeometry(230, 90, 50, 20);

    //  QObject::connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(test()));
    //   button for test
    //  QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(sendMail()));
    //  QObject::connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT());
    //  QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(database()));
    //  QObject::connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(test()));

    getMails();

    QObject::connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(goToFormManaul()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(CloseApp()));
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ValidateLogin()));
}

void MainWindow::sendMail()
{
    qDebug() << "send maile functuion";
    sendMailThread *th = new sendMailThread(this);
    th->initMailThread("benzidane27@gmail.com", "test sub", "hi hello");
    qDebug() << th->str().c_str();
    th->start();
}
void MainWindow::getMails()
{
    WaitingSpinnerWidget *spinner = new WaitingSpinnerWidget(ui->page_8);
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

    getMailsThread *th = new getMailsThread();

    th->start();

    connect(th, &getMailsThread::workFinished, this, [&](QList<QMap<std::string, std::string>> resualt)
            {
                ui->stackedWidget_4->setCurrentIndex(1);
                QVBoxLayout *lay = new QVBoxLayout(ui->widget_49);

                for (QMap<std::string, std::string> msg : resualt)
                {
                    qDebug()<<msg.value("id").c_str();
                    mQWidgetMessage *p = new mQWidgetMessage(msg.value("UID"),msg.value("senderMail"), msg.value("Messagesubject"), "", msg.value("senderDate"),"msg_body");
                    p->TemplateDetails(ui->widget_52,ui->stackedWidget_3,ui->label_32,ui->label_33,ui->label_34,ui->label_35,ui->textBrowser);
                    lay->addWidget(p);

                }
                qDebug() << "###done###"; });
};
void MainWindow::database()
{
    qDebug() << "database";

    /*
  ////database connection////
   Database &db = Database::getInstance();

   if (db.get_Db().open())
   {
       qDebug() << "found database";
       QSqlQuery query;
       query = db.get_Db().exec("select * from User");

       qDebug() << "this size of data is: "
                << "";

       while (query.next())
       {
           User u(query);
           qDebug() << u.toJson();
       }

       // Map map;
       // // map.insert("id", "01");
       // map.insert("first_name", "amine");
       // map.insert("last_name", "ben");
       // map.insert("email", "ben@g.com");
       // map.insert("password", "123456");

       // User user =User::fromJson(map);
       // user.save();
       // qDebug()<<user.toJson();
   }
   else
   {
       qDebug() << "not found database";
   }
  */
};
void MainWindow::test()
{

    // QPropertyAnimation *animation = new QPropertyAnimation(this->ui->label_14, "rotation",this);

    // animation->setDuration(1000);
    // animation->setStartValue(0);
    // animation->setEndValue(360);
    // animation->start(QPropertyAnimation::DeleteWhenStopped);

    // std::ostringstream oss;
    // int x = 1;
    // Map map;
    // map.insert("id", "01");
    // map.insert("first_name", "amine");
    // map.insert("last_name", "ben");
    // map.insert("email", "ben@g.com");
    // map.insert("password", "123456");

    // User user = User::fromJson(map);

    // oss << " hell " << user << " d";

    // qDebug() << user;
    qDebug() << "hello how are you";
};

void MainWindow::CloseApp()
{
    this->close();
}

void MainWindow::ValidateLogin()
{
    std::vector<std::string> EmailErrorsList;
    std::vector<std::string> PassErrorsList;

    Email_str = ui->lineEdit->text().toStdString();
    Pass_str = ui->lineEdit_2->text().toStdString();

    std::regex EmailPattern(R"([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4}))");

    if (!std::regex_match(Email_str, EmailPattern))
        EmailErrorsList.push_back("enter a valid email");

    if (Pass_str.size() < 6)
        PassErrorsList.push_back("password too short");

    if (PassErrorsList.empty() and PassErrorsList.empty())
    {
        ui->label_5->setStyleSheet("*{color:#136F5F;}");
        ui->lineEdit->setStyleSheet("*{border:1px solid #136F5F;}");
        ui->lineEdit_2->setStyleSheet("*{border:1px solid #136F5F;}");
        ui->label_5->setText("good!");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        if (EmailErrorsList.empty())
        {
            ui->label_5->setText(QString::fromStdString(""));
            ui->label_5->setStyleSheet("*{color:black;}");
            ui->lineEdit->setStyleSheet("*{border:1px solid #136F5F;}");
        }
        if (PassErrorsList.empty())
        {
            ui->label_5->setText(QString::fromStdString(""));
            ui->label_5->setStyleSheet("*{color:black;}");
            ui->lineEdit_2->setStyleSheet("*{border:1px solid #136F5F;}");
        }
        if (not PassErrorsList.empty())
        {

            ui->label_5->setText(QString::fromStdString(PassErrorsList[0]));
            ui->label_5->setStyleSheet("*{color:red;}");
            ui->lineEdit_2->setStyleSheet("*{border:1px solid red;}");
        }
        if (not EmailErrorsList.empty())
        {
            ui->label_5->setStyleSheet("*{color:red;}");
            ui->label_5->setText(QString::fromStdString(EmailErrorsList[0]));
            ui->lineEdit->setStyleSheet(QString::fromStdString("*{border:1px solid red;}"));
        }
    }

}
void MainWindow::goToFormManaul()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    qDebug() << "bye ***";

    delete ui;
}
