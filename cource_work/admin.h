#ifndef ADMIN_H
#define ADMIN_H

#include <QDate>
#include <QMainWindow>
#include <Programm.h>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
    void refreshJournal();
    void refreshGuests();
    void setProgramm(Programm *p);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();




    void on_comboBox_activated(const QString &arg1);

private:
    Ui::Admin *ui;
    Programm *programm;
    QDate date;
    QTime time;
};

#endif // ADMIN_H
