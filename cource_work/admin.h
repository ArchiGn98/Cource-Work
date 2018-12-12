#ifndef ADMIN_H
#define ADMIN_H

#include <QDate>
#include <QMainWindow>
#include "programm.h"
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QTextDocument>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow {
    Q_OBJECT

public:
    explicit Admin(QWidget* parent = nullptr);
    ~Admin();
    void refreshJournal();
    void refreshGuests();
    void refreshWorkers();
    void setProgramm(Programm* p);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_activated(const QString& arg1);

    void on_print_clicked();

    void on_add_clicked();

    void on_addBtn_clicked();

private:
    Ui::Admin* ui;
    Programm* programm;
    QDate date;
    QTime time;
    QPrinter printer;
};

#endif // ADMIN_H
