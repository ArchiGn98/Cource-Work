#ifndef DATA_H
#define DATA_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquery.h>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QDate>
#include <vector>

class Programm
{
private:
    const QString dataBaseName = "programm";
    const QString queryCreateTableCompetition = "CREATE TABLE IF NOT EXISTS competition(id INTEGER PRIMARY KEY autoincrement,"
                                                "discipline TEXT, description TEXT)";
    const QString queryCreateTableGuest = "CREATE TABLE IF NOT EXISTS guest(id INTEGER PRIMARY KEY autoincrement,"
                                                "name_surname TEXT, contacts TEXT, description TEXT, password INTEGER, login TEXT)";
    const QString queryCreateTableEfir = "CREATE TABLE IF NOT EXISTS efir(id INTEGER PRIMARY KEY autoincrement,"
                                                "name TEXT, time_start DATETIME, time_end DATETIME)";
    const QString queryCreateTableParticipant = "CREATE TABLE IF NOT EXISTS participant(id INTEGER PRIMARY KEY autoincrement,"
                                                "name_surname TEXT, biography TEXT, achivements TEXT, facts TEXT, result TEXT)";
    const QString queryCreateTableWorker = "CREATE TABLE IF NOT EXISTS worker(id INTEGER PRIMARY KEY autoincrement,"
                                                "name_surname TEXT, position TEXT, contacts TEXT, password INTEGER, login TEXT)";
    const QString queryCreateTableProgramm = "CREATE TABLE IF NOT EXISTS programm(id INTEGER PRIMARY KEY autoincrement,"
                                                "title TEXT, id_efir INTEGER, FOREIGN KEY (id_efir) REFERENCES efir(id))";
    const QString queryCreateTableStory = "CREATE TABLE IF NOT EXISTS story(id INTEGER PRIMARY KEY autoincrement,"
                                                "description TEXT, titile TEXT, "
                                          "id_programm INTEGER, FOREIGN KEY (id_programm) REFERENCES programm(id))";
    const QString queryCreateTableProgramm_Guest = "CREATE TABLE IF NOT EXISTS programm_guest(id_programm INTEGER, id_guest INTEGER,"
                                                   " FOREIGN KEY (id_programm) REFERENCES programm(id), "
                                                   "FOREIGN KEY (id_guest) REFERENCES guest(id))";
    const QString queryCreateTableProgramm_Competition = "CREATE TABLE IF NOT EXISTS programm_competition(id_programm INTEGER, id_competition INTEGER,"
                                                   " FOREIGN KEY (id_programm) REFERENCES programm(id), "
                                                   "FOREIGN KEY (id_competition) REFERENCES competition(id))";
    const QString queryCreateTableStory_Worker = "CREATE TABLE IF NOT EXISTS story_worker(id_story INTEGER, id_worker INTEGER,"
                                                   " FOREIGN KEY (id_story) REFERENCES story(id), "
                                                   "FOREIGN KEY (id_worker) REFERENCES worker(id))";
    const QString queryCreateTableParticipant_Competition= "CREATE TABLE IF NOT EXISTS participant_competition(id_participant INTEGER, id_competition INTEGER,"
                                                   " FOREIGN KEY (id_participant) REFERENCES participant(id), "
                                                   "FOREIGN KEY (id_competition) REFERENCES competition(id))";
    const QString queryCreateTableJournal = "CREATE TABLE IF NOT EXISTS journal(id INTEGER PRIMARY KEY autoincrement,"
                                                "date DATE, time TIME, username TEXT, action TEXT)";
    QSqlDatabase *db;
    QSqlQuery *qry;
    QDate date;
    QTime time;

    bool fillCompetition(const QString &dicipline, const QString &description);

    bool fillParticipant(const QString &name_surname, const QString &bio, const QString &achivements, const QString &facts, const QString &result);
    bool fillProgramm_competition(int id_programm, int id_competition);
    bool fillParticipant_competition(int id_participant, int id_competition);
    bool testData();
    void showCompetition();
    void showEfir();
    int getProgrammId(const QString &name);
    int getStoryId(const QString &title);
    int getWorkerId(const QString &name);

public:
    Programm();
    bool fillEfir(const QString &name, const QString &time_start, const QString &time_end);
    bool fillProgramm(const QString &titile, int id_efir);
    bool launch();
    bool insertGuest(const QString &name_surname, const QString &contacts, const QString &description, int password, const QString &login);
    bool insertWorker(const QString &name_surname, const QString &position, const QString &contacts, int password, const QString &login);
    bool insertStory(const QString &description, const QString &title);
    bool insertJournal(const QString &date, const QString &time, const QString &username, const QString &action);
    bool insertProgramm_Guest(int programm_id, int guest_id);
    bool insertProgramm_Guest(const QString &name,const QString &programm_title);
    bool insertWorker_Story(const QString &worker_nickname, const QString &programm_name, const QString &story_title, const QString &story_text);
    void selectFromJournal(const QString &str);
    void selectFromGuests();
    void selectFromWorkers();
    void selectFromProgramms_Efir();
    void selectFromProgrammsWideInfo(const QString &title);
    QSqlDatabase getDb();
    Programm &operator=(Programm &&source);
    Programm &operator=(Programm &source);
    Programm *operator=(Programm *source);
    QSqlQuery *getQry() const;
    void setQry(QSqlQuery *value);
    bool isGuest(const QString &login, int password);
    bool isGuest(const QString &login);
    bool isWorker(const QString &login, int password);
    bool isWorker(const QString &login);


    void selectGuestsForProgramm(const QString &title);
    void selectStroriesForWorker(const QString &worker);

    int getEfirId(const QString &name);
};

#endif // DATA_H
