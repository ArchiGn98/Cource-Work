#include "Programm.h"
#include <vector>
#include <bits/stl_vector.h>
Programm::Programm()
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(dataBaseName);
    qry = new QSqlQuery(*db);

}

bool Programm::insertGuest(const QString &name_surname, const QString &contacts, const QString &description, int password, const QString &login)
{
    qry->prepare("INSERT INTO guest(name_surname, contacts, description, password, login) VALUES(?,?,?,?,?)");
    qry->addBindValue(name_surname);
    qry->addBindValue(contacts);
    qry->addBindValue(description);
    qry->addBindValue(password);
    qry->addBindValue(login);
    if(qry->exec()){
        qDebug()<<"Inserted Guest: " << name_surname;
        qry->clear();
        date = QDate::currentDate();
        time = QTime::currentTime();
        insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), "NULL", "Insert Guest");
        return true;
    }
    else {
        qDebug()<<"Failed Insert Guest:" << qry->lastError().text();
        qry->clear();
        date = QDate::currentDate();
        time = QTime::currentTime();
        insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), "NULL", "Insert Worker");
        return false;
    }
}

bool Programm::insertWorker(const QString &name_surname, const QString &position, const QString &contacts, int password, const QString &login)
{
    qry->prepare("INSERT INTO worker(name_surname, position, contacts, password, login) VALUES(?,?,?,?,?)");
    qry->addBindValue(name_surname);
    qry->addBindValue(position);
    qry->addBindValue(contacts);
    qry->addBindValue(password);
    qry->addBindValue(login);
    if(qry->exec()){
        qDebug()<<"Inserted Worker: " << name_surname;
        qry->clear();
        date = QDate::currentDate();
        time = QTime::currentTime();
        insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), "NULL", "Insert Worker");
        return true;
    }
    else {
        qDebug()<<"Failed Insert Guest:" << qry->lastError().text();
        qry->clear();
        return false;
    }
}

bool Programm::insertStory(const QString &description, const QString &title)
{
    qry->prepare("INSERT INTO story(description, title) VALUES(?,?)");
    qry->addBindValue(description);
    qry->addBindValue(title);
    if(qry->exec()){
        qDebug()<<"Inserted Story: " << title;
        qry->clear();
        return true;
    }
    else {
        qDebug()<<"Failed Insert Story:" << qry->lastError().text();
        qry->clear();
        return false;
    }
}

bool Programm::insertJournal(const QString &date, const QString &time, const QString &username, const QString &action)
{
    qry->prepare("INSERT INTO journal(date, time, username, action) VALUES(?,?,?,?)");
    qry->addBindValue(date);
    qry->addBindValue(time);
    qry->addBindValue(username);
    qry->addBindValue(action);
    if(qry->exec()){
        qDebug()<<"Inserted Journal: " << action << "  " << date << " " << time;
        qry->clear();
        return true;
    }
    else {
        qDebug()<<"Failed Insert Journal:" << qry->lastError().text();
        qry->clear();
        return false;
    }
}

bool Programm::insertProgramm_Guest(int programm_id, int guest_id)
{
    qry->prepare("INSERT INTO programm_guest(id_programm, id_guest) VALUES(?,?)");
    qry->addBindValue(programm_id);
    qry->addBindValue(guest_id);
    if(qry->exec()){
        qDebug()<<"Inserted Programm_Guest:";
        qry->clear();
        return true;
    }
    else {
        qDebug()<<"Failed Insert Programm_Guest:" << qry->lastError().text();
        qry->clear();
        return false;
    }
}

bool Programm::insertProgramm_Guest(const QString &name, const QString &programm_title)
{
    int programm_id, guest_id;
    qry->prepare("SELECT id, login FROM guest WHERE login = ?");
    qry->addBindValue(name);
    if(qry->exec()){
        qry->next();
        guest_id = qry->value(0).toInt();
        qry->clear();
        qry->prepare("SELECT id, title FROM programm WHERE title = ?");
        qry->addBindValue(programm_title);
        if(qry->exec()){
            qry->next();
            programm_id = qry->value(0).toInt();
            insertProgramm_Guest(programm_id, guest_id);
            qDebug()<<"Insertion programm_guest succesfull:";
            date = QDate::currentDate();
            time = QTime::currentTime();
            insertJournal(date.toString("yyyy-MM-dd"), time.toString("hh:mm:ss"), name, "Insert Program_guest");
            return true;
        }
        else {
            qDebug()<<"Failed find programm id:" << qry->lastError().text();
        }
    }
    else {
        qDebug()<<"Failed find guest id:" << qry->lastError().text();

    }
    return false;
}

bool Programm::insertWorker_Story(int worker_id, int story_id)
{
    qry->prepare("INSERT INTO worker_story(worker_id, story_id) VALUES(?,?)");
    qry->addBindValue(worker_id);
    qry->addBindValue(story_id);
    if(qry->exec()){
        qDebug()<<"Inserted Worker_Strory:";
        qry->clear();
        return true;
    }
    else {
        qDebug()<<"Failed Insert Worker_Strory:" << qry->lastError().text();
        qry->clear();
        return false;
    }
}

void Programm::selectFromJournal(const QString &str)
{
    if(str == "All"){
        qry->prepare("SELECT * FROM journal");
    }
    else if (str == "Registration") {
        qry->prepare("SELECT * FROM journal WHERE action LIKE 'Acc%'");
    }
    else if (str == "Insert in DB") {
        qry->prepare("SELECT * FROM journal WHERE action LIKE 'Insert%'");
    }
    else if (str == "Buttons Push") {
        qry->prepare("SELECT * FROM journal WHERE action LIKE 'Push%'");
    }
    else {
        qry->prepare("SELECT * FROM journal");
    }

    if(qry->exec()){
        qDebug()<<"SELECT SUCCESS";
    }
    else {
        qDebug() << qry->lastError().text();
    }
}

void Programm::selectFromGuests()
{
    qry->prepare("SELECT guest.id, guest.name_surname, programm.title FROM programm JOIN guest JOIN programm_guest "
                 "ON programm_guest.id_programm = programm.id AND programm_guest.id_guest = guest.id");

    if(qry->exec()){
        qDebug()<<"SELECT SUCCESS";
    }
    else {
        qDebug() << qry->lastError().text();
    }
}

void Programm::selectFromProgramms_Efir()
{
    qry->prepare("SELECT programm.id, programm.title, time_start, time_end FROM programm JOIN efir ON programm.id_efir = efir.id");
    if(qry->exec()){
        qDebug()<<"SELECT SUCCESS";
    }
    else {
        qDebug() << qry->lastError().text();
    }
}

void Programm::selectFromProgrammsWideInfo(const QString &title)
{
    qry->prepare("SELECT programm.title, time_start, time_end, discipline, description,"
                 " participant.name_surname, biography, achivements, facts FROM programm JOIN efir JOIN competition JOIN participant"
                 " JOIN programm_competition JOIN participant_competition"
                 " ON programm.id_efir = efir.id AND programm_competition.id_programm = programm.id AND "
                 "programm_competition.id_competition = competition.id AND "
                 "participant_competition.id_participant = participant.id AND "
                 "participant_competition.id_competition = competition.id"
                 " WHERE programm.title = ?");
    qry->addBindValue(title);
    if(qry->exec()){
        qDebug()<<"SELECT SUCCESS";
    }
    else {
        qDebug() << qry->lastError().text();
    }
}

QSqlDatabase Programm::getDb()
{
    return *db;
}

//QSqlQuery Programm::selectFromJournal()
//{
//    qry->exec("SELECT * FROM journal");
//    return *qry;
//}

Programm &Programm::operator=(Programm &&source)
{
    qDebug() << "move constructor Programm";
    if(this==&source){
        return *this;
    }
    delete qry;
    delete db;
    qry = source.qry;
    db = source.db;

    source.qry = nullptr;
    source.db = nullptr;

    return *this;

}
Programm &Programm::operator=(Programm &source)
{
    qDebug() << "copy constructor Programm";
    if(this==&source){
        return *this;
    }
    delete qry;
    delete db;
    qry = source.qry;
    db = source.db;


    return *this;

}

Programm *Programm::operator=(Programm *source)
{
    qDebug() << "copy constructor Programm*";
    if(this==source){
        return this;
    }
    delete qry;
    delete db;
    qry = source->qry;
    db = source->db;



    return this;
}

bool Programm::launch()
{
    qDebug() << "Launching DB...";
    if (db->open()) {
      if (qry->exec(queryCreateTableCompetition))
        qDebug() << "Competition OK.";
      else
        qDebug() << "Competition FAIL.";

      if (qry->exec(queryCreateTableEfir))
        qDebug() << "Efir OK.";
      else
        qDebug() << "Efir FAIL.";

      if (qry->exec(queryCreateTableGuest))
        qDebug() << "Guest OK.";
      else
        qDebug() << "Guest FAIL.";
      if (qry->exec(queryCreateTableJournal))
        qDebug() << "Journal OK.";
      else
        qDebug() << "Journal FAIL.";

      if (qry->exec(queryCreateTableParticipant))
        qDebug() << "Participant OK.";
      else
        qDebug() << "Participant FAIL.";

      if (qry->exec(queryCreateTableParticipant_Competition))
        qDebug() << "Participant_comp OK.";
      else
        qDebug() << "Participant_comp FAIL.";
      if (qry->exec(queryCreateTableProgramm))
        qDebug() << "Programm OK.";
      else
        qDebug() << "programm FAIL.";

      if (qry->exec(queryCreateTableProgramm_Competition))
        qDebug() << "Prog_comp OK.";
      else
        qDebug() << "Prog_comp FAIL.";

      if (qry->exec(queryCreateTableProgramm_Guest))
        qDebug() << "Prog_guest OK.";
      else
        qDebug() << "Prog_guest FAIL.";
      if (qry->exec(queryCreateTableStory))
        qDebug() << "story OK.";
      else
        qDebug() << "story FAIL.";

      if (qry->exec(queryCreateTableStory_Worker))
        qDebug() << "story_worker OK.";
      else
        qDebug() << "story_worker FAIL.";

      if (qry->exec(queryCreateTableWorker))
        qDebug() << "worker OK.";
      else
        qDebug() << "worker FAIL.";
    } else {
      qDebug() << "SQLite Error: " << db->lastError().text();
    }
    qry->clear();

    //testData();

    return true;
}

bool Programm::testData()
{

    fillCompetition("Football","This is football competition in Brazil");
    fillCompetition("Basketball","This is basketball competition in USA");
    fillCompetition("Tenis","This is tenis competition in Peru");
    fillCompetition("Snowboarding","This is snowboarding competition in New Zeland");

    fillEfir("Morning","2018-12-28 12:45:00","2018-12-28 14:45:00");
    fillEfir("Evening","2018-12-28 19:45:00","2018-12-28 21:45:00");


    fillParticipant("Nikola Sturman", "Norwey sportsman. Burned 13.09.1974 in Africa.", "3 gold medals", "loves unicornes", "good");
    fillParticipant("Misha Sapkovskii", "British sportsman. Burned 11.12.1968", "2 silver medals", "loves mashrooms", "awesome");
    fillParticipant("Ketlen Stark", "Ukranian sportsman. Borned 11.07.2010", "1 bronze medal", "loves killing", "bad");
    fillParticipant("Midena Jolen", "Russian sportsman. Borned 04.09.1986", "5 gold medals", "loves cource works", "good");
    fillParticipant("Lyona Externov", "Bulgarian sportsman. Burned 06.03.1982", "3 gold medals", "loves unicornes", "bad");
    fillParticipant("Pol Lartni", "French sportsman. Didnt borne yet", "10 silver medals", "loves to eat but cant afford this", "awesome");
    fillParticipant("Kemper Battlefield", "Just sportsman. Borned in India 11.05.2000", "0 gold medals", "loves hot chairs", "good");

    fillParticipant_competition(1,1);
    fillParticipant_competition(2,1);
    fillParticipant_competition(3,2);
    fillParticipant_competition(4,2);
    fillParticipant_competition(5,3);
    fillParticipant_competition(6,3);
    fillParticipant_competition(7,4);
    fillParticipant_competition(1,4);

    fillProgramm("Good morning USA",1);
    fillProgramm("Good evening USA",2);

    fillProgramm_competition(1,1);
    fillProgramm_competition(1,2);
    fillProgramm_competition(2,3);
    fillProgramm_competition(2,4);

    showCompetition();
    showEfir();
    return true;
}

void Programm::showCompetition()
{
    qry->prepare("SELECT discipline, description FROM competition");
    std::vector<QString> diciplines;
    std::vector<QString> descriptions;
    if(qry->exec()){
        while (qry->next()) {
            diciplines.push_back(qry->value(0).toString());
            descriptions.push_back(qry->value(1).toString());
        }
        for(size_t i = 0; i < diciplines.size(); ++i){
            qDebug()<< "==================================";
            qDebug()<< "Dicipline: " << diciplines.at(i);
            qDebug()<< "Description: " << descriptions.at(i);
        }
        qDebug()<< "==================================";
    }
    else {
        qDebug()<< "Failed show competition";
    }
}

void Programm::showEfir()
{
    qry->prepare("SELECT time_start, time_end FROM efir");
    std::vector<QString> start;
    std::vector<QString> end;
    if(qry->exec()){
        while (qry->next()) {
            start.push_back(qry->value(0).toString());
            end.push_back(qry->value(1).toString());
        }
        for(size_t i = 0; i < start.size(); ++i){
            qDebug()<< "==================================";
            qDebug()<< "Start: " << start.at(i);
            qDebug()<< "End: " << end.at(i);
        }
        qDebug()<< "==================================";
    }
    else {
        qDebug()<< "Failed show Efir";
    }
}


QSqlQuery *Programm::getQry() const
{
    return qry;
}

void Programm::setQry(QSqlQuery *value)
{
    qry = value;
}

bool Programm::isGuest(const QString &login, int password)
{
    qry->prepare("SELECT * FROM guest WHERE login = ? AND password = ?");
    qry->addBindValue(login);
    qry->addBindValue(password);
    if(qry->exec()){
        if(qry->next()){
            return true;
        }
    }
    while(qry->next()){
        qDebug()<<qry->value(0).toString();
        qDebug()<<qry->value(1).toString();
        qDebug()<<qry->value(2).toString();
        qDebug()<<qry->value(3).toString();
        qDebug()<<qry->value(4).toString();
        qDebug()<<qry->value(5).toString();
    }
    return false;
}

bool Programm::isGuest(const QString &login)
{
    qry->prepare("SELECT * FROM guest WHERE login = ?");
    qry->addBindValue(login);
    if(qry->exec()){
        if(qry->next()){
            return true;
        }
    }

    return false;
}

bool Programm::isWorker(const QString &login)
{
    qry->prepare("SELECT * FROM worker WHERE login = ?");
    qry->addBindValue(login);
    if(qry->exec()){
        if(qry->next()){
            return true;
        }
    }
    return false;
}

bool Programm::fillCompetition(const QString &dicipline, const QString &description)
{
    qry->prepare("INSERT INTO competition(discipline, description) VALUES(?,?)");
    qry->addBindValue(dicipline);
    qry->addBindValue(description);
    if(qry->exec()){
        qDebug()<<"Inserted Competition: " << dicipline;
        qry->clear();
        return true;
    }
    else {
        qDebug()<<"Failed Insert Competition:" << qry->lastError().text();
        qry->clear();
        return false;
    }
}

bool Programm::fillEfir(const QString &name, const QString &time_start, const QString &time_end)
{
    qry->prepare("INSERT INTO efir(name, time_start, time_end) VALUES(?,?,?)");
    qry->addBindValue(name);
    qry->addBindValue(time_start);
    qry->addBindValue(time_end);
    if(qry->exec()){
        qDebug()<<"Inserted Efir: " << name;
        qry->clear();
        return true;
    }
    else {
        qDebug()<<"Failed Insert Efir: " << qry->lastError().text();
        qry->clear();
        return false;
    }
}

bool Programm::fillParticipant(const QString &name_surname, const QString &bio, const QString &achivements, const QString &facts, const QString &result)
{
    qry->prepare("INSERT INTO participant(name_surname, biography, achivements, facts, result) VALUES(?,?,?,?,?)");
    qry->addBindValue(name_surname);
    qry->addBindValue(bio);
    qry->addBindValue(achivements);
    qry->addBindValue(facts);
    qry->addBindValue(result);
    if(qry->exec()){
        qDebug()<<"Inserted Participant: " << name_surname;
        qry->clear();
        return true;
    }
    else {
        qDebug()<<"Failed Insert Participant" << qry->lastError().text();
        qry->clear();
        return false;
    }
}

bool Programm::fillProgramm(const QString &title, int id_efir)
{
    qry->prepare("INSERT INTO programm(title, id_efir) VALUES(?,?)");
    qry->addBindValue(title);
    qry->addBindValue(id_efir);
    if(qry->exec()){
        qDebug()<<"Inserted Programm: " << title;
        qry->clear();
        return true;
    }
    else {
        qDebug()<<"Failed Insert Programm" << qry->lastError().text();
        qry->clear();
        return false;
    }
}

bool Programm::fillProgramm_competition(int id_programm, int id_competition)
{
    qry->prepare("INSERT INTO programm_competition(id_programm, id_competition) VALUES(?,?)");
    qry->addBindValue(id_programm);
    qry->addBindValue(id_competition);
    if(qry->exec()){
        qDebug()<<"Inserted Programm_Competition:";
        qry->clear();
        return true;
    }
    else {
        qDebug()<<"Failed Insert Programm_competition: " << qry->lastError().text();
        qry->clear();
        return false;
    }
}

bool Programm::fillParticipant_competition(int id_participant, int id_competition)
{
    qry->prepare("INSERT INTO participant_competition(id_participant, id_competition) VALUES(?,?)");
    qry->addBindValue(id_participant);
    qry->addBindValue(id_competition);
    if(qry->exec()){
        qDebug()<<"Inserted Participant_Competition:";
        qry->clear();
        return true;
    }
    else {
        qDebug()<<"Failed Insert Participant_competition: " << qry->lastError().text();
        qry->clear();
        return false;
    }
}





