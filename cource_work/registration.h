#ifndef REGISTRATION_H
#define REGISTRATION_H
#include<Programm.h>
#include <QDate>
#include <QMainWindow>

namespace Ui {
class Registration;
}

class Registration : public QMainWindow
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();
    void setProgramm(Programm *p);

private slots:
    void on_guest_btn_clicked();

    void on_worker_btn_clicked();

    void on_pushButton_clicked();

    void on_create_clicked();

    void on_create_2_clicked();

    void on_back_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Registration *ui;
    Programm *programm;
    QDate date;
    QTime time;
};

#endif // REGISTRATION_H
