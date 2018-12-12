#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Admin)
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
    ui->journal->setColumnWidth(4, 190);
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
    ui->guests->setColumnWidth(1, 200);
    ui->guests->setColumnWidth(2, 200);
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
    ui->guests->setColumnWidth(2, 200);
    ui->guests->setColumnWidth(3, 300);
    ui->workers->setStyleSheet("background-color:#fcfcfc; gridline-color: #e8560d;");

    ui->comboBox->addItems(stringsList);
    ui->pushButton->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->pushButton_2->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->comboBox->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");

    ui->Jounal->setStyleSheet("color: #fcfcfc; font:24pt");
    ui->Guests->setStyleSheet("color: #fcfcfc; font:24pt");
    ui->workers_label->setStyleSheet("color: #fcfcfc; font:24pt");

    ui->addTitle->setStyleSheet("background-color:#6b6b6b; color: #fcfcfc; border-color:#777777;font:16pt;border: 0px;");
    ui->addBtn->setStyleSheet("background-color:#e8560d; color: #fcfcfc; padding:10px; font: 16pt");
    ui->addLabel->setStyleSheet("color: #fcfcfc; font:24pt");

    ui->mainW->setVisible(true);
    ui->addW->setVisible(false);

}

Admin::~Admin()
{
    delete ui;
}

void Admin::refreshJournal()
{
    int n = ui->journal->rowCount();
    for (int i = 0; i < n; i++)
        ui->journal->removeRow(0);

    programm->selectFromJournal(ui->comboBox->currentText());

    while (programm->getQry()->next()) {
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
    for (int i = 0; i < n; i++)
        ui->guests->removeRow(0);

    programm->selectFromGuests();

    while (programm->getQry()->next()) {
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
    for (int i = 0; i < n; i++)
        ui->workers->removeRow(0);

    programm->selectFromWorkers();

    while (programm->getQry()->next()) {
        ui->workers->insertRow(0);
        ui->workers->setItem(0, 0, new QTableWidgetItem(programm->getQry()->value(0).toString()));
        ui->workers->setItem(0, 1, new QTableWidgetItem(programm->getQry()->value(1).toString()));
        ui->workers->setItem(0, 2, new QTableWidgetItem(programm->getQry()->value(2).toString()));
        ui->workers->setItem(0, 3, new QTableWidgetItem(programm->getQry()->value(3).toString()));
        ui->workers->setRowHeight(0, 20);
    }
}

void Admin::setProgramm(Programm* p)
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

void Admin::on_comboBox_activated(const QString& arg1)
{
    programm->selectFromJournal(arg1);
}

void Admin::on_print_clicked()
{
    QString result;
    std::vector<QString> titles;
    programm->getQry()->prepare("SELECT title FROM programm");
    if(programm->getQry()->exec()){
        while(programm->getQry()->next()){
            titles.push_back(programm->getQry()->value(0).toString());
        }
    }
    for(auto a: titles){
        programm->selectGuestsForProgramm(a);
        result += "<b>" + a + "</b>";
        result += ": <br>";
        while (programm->getQry()->next()) {
            if(programm->getQry()->value(0).toString() == ""){
                result += "NONE";
            }
            else {
                result += programm->getQry()->value(0).toString();
            }

            result += "             ";
        }
        result += "<br>";
    }

//    QString result2;
//    std::vector<QString> workers;
//    programm->getQry()->prepare("SELECT name_surname FROM worker");
//    if(programm->getQry()->exec()){
//        while(programm->getQry()->next()){
//            workers.push_back(programm->getQry()->value(0).toString());
//        }
//    }
//    for(auto a: workers){
//        programm->selectStroriesForWorker(a);
//        result2 += "<b>" + a + "</b>";
//        result2 += ": <br>";
//        while (programm->getQry()->next()) {
//            if(programm->getQry()->value(0).toString() == ""){
//                result2 += "NONE";
//            }
//            else {
//                result2 += programm->getQry()->value(0).toString();
//            }

//            result2 += "             ";
//        }
//        result2 += "<br>";
//    }


    QString result3;
    programm->getQry()->prepare("SELECT efir.name "
                                "FROM efir "
                                "WHERE efir.time_start BETWEEN '2018-12-28 12:45:00' AND '2018-12-28 17:45:00'");
    if(programm->getQry()->exec()){
        while(programm->getQry()->next()){
            result3+= programm->getQry()->value(0).toString();
        }
        result3 += "<br>";
    }


    QString htmlStart =
    "<h1 align=center>ОТЧЕТ</h1>"
    "<p align=justify>";
    QString htmlEnd = "Guests in programs:<br>"+ result + "<br><br><b>Efir start between '2018-12-28 12:45:00' AND '2018-12-28 17:45:00'</b> <br>" + result3 + "</p>";
    QString html = htmlStart + htmlEnd;

    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("/program.pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    document.print(&printer);
}

void Admin::on_add_clicked()
{
    ui->mainW->setVisible(false);
    ui->addW->setVisible(true);
}

void Admin::on_addBtn_clicked()
{
    QString efirName = + "Efir: " + ui->addTitle->text();
    programm->fillEfir(efirName, ui->addStart->text(), ui->addEnd->text());
    int id_efir = programm->getEfirId(efirName);
    programm->fillProgramm(ui->addTitle->text(), id_efir);
    ui->mainW->setVisible(true);
    ui->addW->setVisible(false);
}
