#ifndef GUEST_H
#define GUEST_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QDebug>
#include <Programm.h>
namespace Ui {
class Guest;
}

class Guest : public QMainWindow
{
    Q_OBJECT

public:
    explicit Guest(QWidget *parent = nullptr);
    ~Guest();
    void setName(const QString &name);
    void setProgramm(Programm *p);
private slots:


    void on_pushButton_clicked();

    void on_programms_itemClicked(QTableWidgetItem *item);

    void on_back_clicked();

    void on_ok_clicked();

private:
    Ui::Guest *ui;
    Programm * programm;
    QString name;
    QTime time;
    QDate date;
    void refreshProgramms();
};

#endif // GUEST_H
