#include "mainwindow.h"
#include <QDebug>

#include <QApplication>
#include <QPushButton>
#include <QString>
#include <QRect>
#include <QLabel>
#include <QMessageBox>

//sudo apt install qtbase5-dev
void sayhe(){
     qDebug() << "goood";
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton btn;

    MainWindow w;

    // w.setWindowTitle(QString("hello"));
    // QLabel lab(&w);
    // lab.setText(QString("hello world"));
    // lab.setGeometry(70,80,120,100);
    // btn.setText(QString("click me"));
    // btn.setParent(&w);
    // btn.setGeometry(QRect(0,0,60,30));
    // QObject::connect(&btn, &QPushButton::click, &sayhe);


    w.show();
    return a.exec();
}
