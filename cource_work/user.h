#ifndef GUEST_H
#define GUEST_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QDebug>
#include "Programm.h"
namespace Ui {
class User;
}

class User : public QMainWindow {
    Q_OBJECT

public:
    explicit User(QWidget* parent = nullptr);
    ~User();
    void setName(const QString& name);
    void setUser(const QString& name);
    void setProgramm(Programm* p);

private slots:

    void on_pushButton_clicked();

    void on_programms_itemClicked(QTableWidgetItem* item);

    void on_back_clicked();

    void on_ok_clicked();

    void on_story_apply_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::User* ui;
    Programm* programm;
    QString name, user;
    QTime time;
    QDate date;
    void refreshProgramms();
};

#endif // GUEST_H
