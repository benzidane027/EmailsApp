#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <filesystem>
#include "maillHandler.h"



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
    void getMails();
    void database();
    void test();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
