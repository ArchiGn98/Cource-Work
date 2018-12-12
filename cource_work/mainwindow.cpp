#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

//LOGIN

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    registration = new Registration();
    admin = new Admin();
    user = new User();
    ui->setupUi(this);

    ui->centralWidget->setStyleSheet("background-color:#515151;");
    ui->label->setStyleSheet("color: #e8560d;font: 36pt");

    ui->label_login->setStyleSheet("color: #fcfcfc; font:24pt");
    ui->label_login_2->setStyleSheet("color: #fcfcfc;font:18pt");
    ui->username->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px ;");
    ui->password->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->password->setEchoMode(QLineEdit::Password);
    ui->sign->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->register_2->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    programm = new Programm();
    programm->launch();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete programm;
}

void MainWindow::on_sign_clicked()

{

    QString nickname;
    int password;
    bool isNumb;
    nickname = ui->username->text();
    password = ui->password->text().toInt(&isNumb, 10);
    if (isNumb) {
        if (nickname == "admin" && password == 123456) {
            admin->setProgramm(programm);
            admin->show();
        }
        else {
            if (isNumb) {
                if (programm->isGuest(nickname, password)) {
                    user->setName(nickname);
                    user->setProgramm(programm);
                    user->setUser("Guest");
                    user->show();
                    date = QDate::currentDate();
                    time = QTime::currentTime();
                    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), nickname, "Login Guest");
                }
                else if (programm->isWorker(nickname, password)) {
                    user->setName(nickname);
                    user->setProgramm(programm);
                    user->setUser("Worker");
                    user->show();
                    date = QDate::currentDate();
                    time = QTime::currentTime();
                    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), nickname, "Login Worker");
                }
                else {
                    QMessageBox::information(this, "Password Error", "This user does't exist, try one more time!");
                }
            }
            else {
                QMessageBox::information(this, "Password Error", "Password can be only number");
            }
            date = QDate::currentDate();
            time = QTime::currentTime();
            programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), "NULL", "Push Login");
        }
    }
}

void MainWindow::on_register_2_clicked()
{
    date = QDate::currentDate();
    time = QTime::currentTime();
    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), "NULL", "Push Register");
    registration->setProgramm(programm);
    registration->show();
}
