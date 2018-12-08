#include "guest.h"
#include "ui_guest.h"

Guest::Guest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Guest)
{
    ui->setupUi(this);

    ui->centralwidget->setStyleSheet("background-color:#515151;");
    ui->welcome->setStyleSheet("color: #fcfcfc;font: 36pt");
    ui->programms->setColumnCount(4);
    ui->programms->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("ID")));
    ui->programms->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Title")));
    ui->programms->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Efir_Start")));
    ui->programms->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Efir_End")));
    ui->programms->setShowGrid(true);
    ui->programms->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->programms->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->programms->setColumnHidden(0, true);
    ui->programms->setColumnWidth(1,415);
    ui->programms->setColumnWidth(2,415);
    ui->programms->setColumnWidth(3,415);
    ui->programms->setStyleSheet("background-color:#fcfcfc; gridline-color: #e8560d;");
    ui->pushButton->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->widget->setVisible(true);
    ui->widget_2->setVisible(false);

    ui->title->setStyleSheet("color: #fcfcfc;font: 36pt");
    ui->end->setStyleSheet("color: #fcfcfc;font:18pt");
    ui->start->setStyleSheet("color: #fcfcfc;font:18pt");
    ui->disiplines->setStyleSheet("color: #fcfcfc;font:18pt");
    ui->participants->setStyleSheet("color: #fcfcfc;font:18pt");
    ui->info_deciplines->setStyleSheet("color: #fcfcfc;font:12pt");
    ui->info_participants->setStyleSheet("color: #fcfcfc;font:10pt");

    ui->back->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->ok->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
}

Guest::~Guest()
{
    delete ui;
}

void Guest::setName(const QString &name)
{
    this->name = name;
}

void Guest::setProgramm(Programm *p)
{
    programm = p;
}



void Guest::refreshProgramms()
{
    int n = ui->programms->rowCount();
         for( int i = 0; i < n; i++ ) ui->programms->removeRow( 0 );

         programm->selectFromProgramms_Efir();

         while (programm->getQry()->next())
         {
              ui->programms->insertRow(0);
              ui->programms->setItem(0, 0, new QTableWidgetItem(programm->getQry()->value(0).toString()));
              ui->programms->setItem(0, 1, new QTableWidgetItem(programm->getQry()->value(1).toString()));
              ui->programms->setItem(0, 2, new QTableWidgetItem(programm->getQry()->value(2).toDateTime().toString()));
              ui->programms->setItem(0, 3, new QTableWidgetItem(programm->getQry()->value(3).toDateTime().toString()));
              ui->programms->setRowHeight(0, 20);
         }
}



void Guest::on_pushButton_clicked()
{
    QString welcome = "Welcome, " + name;
    ui->welcome->setText(welcome);
    refreshProgramms();
    date = QDate::currentDate();
    time = QTime::currentTime();
    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), name, "Push Refresh Btn From Wide Mode");
}

void Guest::on_programms_itemClicked(QTableWidgetItem *item)
{
    qDebug()<<item->text();
    ui->widget->setVisible(false);
    ui->widget_2->setVisible(true);
    ui->title->setText(item->text());
    QString start = "start: " + ui->programms->item(item->row(),2)->text();
    QString end = "end: " + ui->programms->item(item->row(),3)->text();
    ui->start->setText(start);
    ui->end->setText(end);

    //get diciplines info
    programm->selectFromProgrammsWideInfo(ui->title->text());
    QString dicipline_info = "", participants_info= "",dicipline, participant;
    while(programm->getQry()->next()){
        if(dicipline == programm->getQry()->value(3).toString()) continue;
        dicipline = programm->getQry()->value(3).toString();
        dicipline_info+=programm->getQry()->value(3).toString()+"\n";
        dicipline_info+=programm->getQry()->value(4).toString();
    }
    programm->getQry()->clear();
    ui->info_deciplines->setText(dicipline_info);

    //get participants info
    programm->selectFromProgrammsWideInfo(ui->title->text());
    while(programm->getQry()->next()){
        if(participant == programm->getQry()->value(5).toString()) continue;
        participant = programm->getQry()->value(5).toString();
        participants_info+=programm->getQry()->value(5).toString()+"\n";
        participants_info+=programm->getQry()->value(6).toString()+"\n";
        participants_info+=programm->getQry()->value(7).toString()+"\n";
        participants_info+=programm->getQry()->value(8).toString()+"\n";
    }
    programm->getQry()->clear();
    ui->info_participants->setText(participants_info);
    date = QDate::currentDate();
    time = QTime::currentTime();
    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), name, "Push table row");
}


void Guest::on_back_clicked()
{
    ui->widget->setVisible(true);
    ui->widget_2->setVisible(false);
    date = QDate::currentDate();
    time = QTime::currentTime();
    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), name, "Push Back Btn From Wide Mode");
}

void Guest::on_ok_clicked()
{
    date = QDate::currentDate();
    time = QTime::currentTime();
    programm->insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), name, "Push be a guest BTN");
    programm->insertProgramm_Guest(name, ui->title->text());
}
