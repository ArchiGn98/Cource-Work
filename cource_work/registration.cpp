#include "registration.h"
#include "ui_registration.h"

#include <QMessageBox>

Registration::Registration(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
    //programm = new Programm();
    ui->centralwidget->setStyleSheet("background-color:#515151;");
    ui->start->setStyleSheet("background-color:#515151;");
    ui->worker->setStyleSheet("background-color:#515151;");
    ui->guest->setStyleSheet("background-color:#515151;");

    ui->regoster_label->setStyleSheet("color: #fcfcfc; font:24pt");
    ui->registration_label2->setStyleSheet("color: #fcfcfc; font:24pt");
    ui->regoster_label_2->setStyleSheet("color: #fcfcfc; font:24pt");
    ui->who_are_you->setStyleSheet("color: #fcfcfc;font:18pt");

    ui->worker_btn->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->guest_btn->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->create->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->create_2->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->pushButton->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->back->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->pushButton_2->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");

    ui->name_surname->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->name_surname_guest->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->position->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->contacts->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->password->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->password_rep->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->contacts_guest->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->description_guest->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->nickname->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->nickname_guest->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->password_guest->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->password_rep_guest->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->start->setVisible(true);
    ui->worker->setVisible(false);
    ui->guest->setVisible(false);

    ui->password->setEchoMode(QLineEdit::Password);
    ui->password_guest->setEchoMode(QLineEdit::Password);
    ui->password_rep->setEchoMode(QLineEdit::Password);
    ui->password_rep_guest->setEchoMode(QLineEdit::Password);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::setProgramm(Programm* p)
{
    programm = p;
    p = nullptr;
}

void Registration::on_guest_btn_clicked()
{
    ui->start->setVisible(false);
    ui->worker->setVisible(false);
    ui->guest->setVisible(true);
    date = QDate::currentDate();
    time = QTime::currentTime();
    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), "NULL", "Push Guest register");
}

void Registration::on_worker_btn_clicked()
{
    date = QDate::currentDate();
    time = QTime::currentTime();
    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), "NULL", "Push Worker register");
    ui->start->setVisible(false);
    ui->worker->setVisible(true);
    ui->guest->setVisible(false);
}

void Registration::on_pushButton_clicked() //Guest back
{
    date = QDate::currentDate();
    time = QTime::currentTime();
    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), "NULL", "Push Back from guest");
    ui->start->setVisible(true);
    ui->worker->setVisible(false);
    ui->guest->setVisible(false);
}

void Registration::on_create_clicked() //worker
{

    bool isNumb, isNumbRep;
    QString name_surname, contacts, position, nickname;
    int password, password_rep;
    name_surname = ui->name_surname->text();
    contacts = ui->contacts->text();
    position = ui->position->text();
    nickname = ui->nickname->text();
    password = ui->password->text().toInt(&isNumb, 10);
    password_rep = ui->password_rep->text().toInt(&isNumbRep, 10);
    if (password == password_rep) {
        if (isNumb) {
            if (!programm->isWorker(nickname)) {
                programm->insertWorker(name_surname, position, contacts, password, nickname);
                date = QDate::currentDate();
                time = QTime::currentTime();
                programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), nickname, "Acc created: Worker");
                this->hide();
            }
            else {
                QMessageBox::information(this, "Nickname Error", "User with this nickname already exists");
            }
        }
        else {
            QMessageBox::information(this, "Password Error", "Password can be only number");
        }
    }
    else {
        QMessageBox::information(this, "Password Error", "Passwords must be same");
    }
}

void Registration::on_create_2_clicked() //guest
{

    bool isNumb, isNumbRep;
    QString name_surname, contacts, description, nickname;
    int password, password_rep;
    name_surname = ui->name_surname_guest->text();
    contacts = ui->contacts_guest->text();
    description = ui->description_guest->text();
    nickname = ui->nickname_guest->text();
    password = ui->password_guest->text().toInt(&isNumb, 10);
    password_rep = ui->password_rep_guest->text().toInt(&isNumbRep, 10);
    if (password == password_rep) {
        if (isNumb) {
            if (!programm->isGuest(nickname)) {
                programm->insertGuest(name_surname, contacts, description, password, nickname);
                date = QDate::currentDate();
                time = QTime::currentTime();
                programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), nickname, "Acc created: Guest");
                this->hide();
            }
            else {
                QMessageBox::information(this, "Nickname Error", "User with this nickname already exists");
            }
        }
        else {
            QMessageBox::information(this, "Password Error", "Password can be only number");
        }
    }
    else {
        QMessageBox::information(this, "Password Error", "Passwords must be same");
    }
}

void Registration::on_back_clicked() //worker back
{
    date = QDate::currentDate();
    time = QTime::currentTime();
    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), "NULL", "Push Back from worker");
    ui->start->setVisible(true);
    ui->worker->setVisible(false);
    ui->guest->setVisible(false);
}

void Registration::on_pushButton_2_clicked() //выход к главному окну
{
    date = QDate::currentDate();
    time = QTime::currentTime();
    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), "NULL", "Push Back to main");
    hide();
    ui->start->setVisible(true);
    ui->worker->setVisible(false);
    ui->guest->setVisible(false);
}
