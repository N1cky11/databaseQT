#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableWidget>
#include <QSqlQueryModel>
#include <QFileInfo>

class DBmanager
{
public:
    DBmanager(const QString &path) ;
    bool addPerson(const QString &name) ;
    bool personExists(const QString &name,bool found=false) ;
    void printAll();
    bool removeAll() ;
    bool removePerson(const QString &name);
    void cmdControl() ;
    //void operator=(const QString &path) ;
    void updateTable(QTableWidget *tableWidget) ;
    ~DBmanager() ;
private:
    QSqlDatabase m_db ;
};
