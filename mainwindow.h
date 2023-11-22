#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <filesystem>
#include "model/mailhandler.h"
#include "model/model.h"
#include <QWidget>
#include "widget/customwidget.h"
#include "./ui_mainwindow.h"

#include <QObject>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QPropertyAnimation>
#include <QGraphicsRectItem>
#include <regex>
#include <iostream>
#include "loadingWidget/waitingspinnerwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow ;

}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void CloseApp();
    void ValidateLogin();

    void goToFormManaul();

    //for test
    void sendMail();

    void database();
    void test();
public:
    void getMails();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
