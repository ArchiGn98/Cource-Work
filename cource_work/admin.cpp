#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    ui->centralwidget->setStyleSheet("background-color:#515151;");
    ui->journal->setColumnCount(5);
    ui->journal->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("ID")));
    ui->journal->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Date")));
    ui->journal->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Time")));
    ui->journal->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Username")));
    ui->journal->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("Action")));
    ui->journal->setShowGrid(true);
    ui->journal->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->journal->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->journal->setColumnHidden(0, true);
    ui->journal->setColumnWidth(4,190);
    ui->journal->setStyleSheet("background-color:#fcfcfc; gridline-color: #e8560d;");
    QList<QString> stringsList;
    stringsList.append("All");
    stringsList.append("Registration");
    stringsList.append("Login");
    stringsList.append("Insert in DB");
    stringsList.append("Buttons Push");

    ui->guests->setColumnCount(3);
    ui->guests->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("ID")));
    ui->guests->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Name")));
    ui->guests->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Programm")));
    ui->guests->setShowGrid(true);
    ui->guests->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->guests->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->guests->setColumnHidden(0, true);
    ui->guests->setColumnWidth(1,200);
    ui->guests->setColumnWidth(2,200);
    ui->guests->setStyleSheet("background-color:#fcfcfc; gridline-color: #e8560d;");

    ui->workers->setColumnCount(4);
    ui->workers->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("ID")));
    ui->workers->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Name")));
    ui->workers->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Story_title")));
    ui->workers->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Story")));
    ui->workers->setShowGrid(true);
    ui->workers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->workers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->workers->setColumnHidden(0, true);
    ui->guests->setColumnWidth(2,200);
    ui->guests->setColumnWidth(3,300);
    ui->workers->setStyleSheet("background-color:#fcfcfc; gridline-color: #e8560d;");

    ui->comboBox->addItems(stringsList);
    ui->pushButton->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->pushButton_2->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->comboBox->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");

    ui->Jounal->setStyleSheet("color: #fcfcfc; font:24pt");
    ui->Guests->setStyleSheet("color: #fcfcfc; font:24pt");
    ui->workers_label->setStyleSheet("color: #fcfcfc; font:24pt");

}

Admin::~Admin()
{
    delete ui;
}

void Admin::refreshJournal()
{
    int n = ui->journal->rowCount();
         for( int i = 0; i < n; i++ ) ui->journal->removeRow( 0 );

         programm->selectFromJournal(ui->comboBox->currentText());

         while (programm->getQry()->next())
         {
              ui->journal->insertRow(0);
              ui->journal->setItem(0, 0, new QTableWidgetItem(programm->getQry()->value(0).toString()));
              ui->journal->setItem(0, 1, new QTableWidgetItem(programm->getQry()->value(1).toDate().toString()));
              ui->journal->setItem(0, 2, new QTableWidgetItem(programm->getQry()->value(2).toTime().toString()));
              ui->journal->setItem(0, 3, new QTableWidgetItem(programm->getQry()->value(3).toString()));
              ui->journal->setItem(0, 4, new QTableWidgetItem(programm->getQry()->value(4).toString()));
              ui->journal->setRowHeight(0, 20);
         }
}

void Admin::refreshGuests()
{
    int n = ui->guests->rowCount();
         for( int i = 0; i < n; i++ ) ui->guests->removeRow( 0 );

         programm->selectFromGuests();

         while (programm->getQry()->next())
         {
              ui->guests->insertRow(0);
              ui->guests->setItem(0, 0, new QTableWidgetItem(programm->getQry()->value(0).toString()));
              ui->guests->setItem(0, 1, new QTableWidgetItem(programm->getQry()->value(1).toString()));
              ui->guests->setItem(0, 2, new QTableWidgetItem(programm->getQry()->value(2).toString()));
              ui->guests->setRowHeight(0, 20);
         }
}

void Admin::refreshWorkers()
{
    int n = ui->workers->rowCount();
         for( int i = 0; i < n; i++ ) ui->workers->removeRow( 0 );

         programm->selectFromWorkers();

         while (programm->getQry()->next())
         {
              ui->workers->insertRow(0);
              ui->workers->setItem(0, 0, new QTableWidgetItem(programm->getQry()->value(0).toString()));
              ui->workers->setItem(0, 1, new QTableWidgetItem(programm->getQry()->value(1).toString()));
              ui->workers->setItem(0, 2, new QTableWidgetItem(programm->getQry()->value(2).toString()));
              ui->workers->setItem(0, 3, new QTableWidgetItem(programm->getQry()->value(3).toString()));
              ui->workers->setRowHeight(0, 20);
         }
}

void Admin::setProgramm(Programm *p)
{
    programm = p;
    p = nullptr;

}

void Admin::on_pushButton_2_clicked()
{
        refreshJournal();
        refreshGuests();
        refreshWorkers();
}

void Admin::on_pushButton_clicked()
{
    hide();
}






void Admin::on_comboBox_activated(const QString &arg1)
{
     programm->selectFromJournal(arg1);
}
