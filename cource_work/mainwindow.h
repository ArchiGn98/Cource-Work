#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <registration.h>
#include <admin.h>
#include "Programm.h"
#include <user.h>
#include <QDate>
#include <memory>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    void on_sign_clicked();

    void on_register_2_clicked();

private:
    Ui::MainWindow* ui;
    Registration* registration;
    Programm* programm;
    Admin* admin;
    User* user;
    QDate date;
    QTime time;
};

#endif // MAINWINDOW_H
