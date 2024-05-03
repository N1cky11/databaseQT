#include "dbmanager.h"

DBmanager::DBmanager(const QString &path) {
    m_db=QSqlDatabase::addDatabase("QSQLITE") ;
    m_db.setDatabaseName(path) ;

    if(!m_db.open() ) {
        throw std::invalid_argument("Can't open database\n") ;
    } else {
        qDebug() << "Opened database" ;
    }
}

bool DBmanager::addPerson(const QString &name)  {
    bool success{false} ;
    QSqlQuery query{} ;
    query.prepare("INSERT INTO people (name) VALUES (:name) ") ;
    query.bindValue(":name",name) ;
    if(query.exec() ) {
        success=true ;
    } else {
        qDebug() << "addPerson error:" << query.lastError().text() ;
    }
    return success ;
}

bool DBmanager::personExists(const QString &name,bool found) {
  QSqlQuery query ;
  query.prepare("SELECT name FROM people WHERE name = (:name)") ;
  query.bindValue(":name",name) ;
  if(query.exec() ) {
      if(query.next() ) {
          found=true ;
      }
  } else {
     qDebug() << "PersonExists error :" << query.lastError().text() ;
  }

    return found ;
}

bool DBmanager::removePerson(const QString &name) {
    bool success=false ;
    if(personExists(name) ) {
        QSqlQuery queryDelete ;
        queryDelete.prepare("DELETE FROM people WHERE name = (:name)") ;
        queryDelete.bindValue(":name",name) ;
        success=queryDelete.exec() ;
        if(!success) {
            qDebug() << "remove person failed" ;
        }

      } else {
        qDebug() << "person doesnt exist" ;
 }
    return success ;
}


bool DBmanager::removeAll() {
   bool success=false ;
   QSqlQuery removeQuery ;
   removeQuery.prepare("DELETE FROM PEOPLE") ;
   if(removeQuery.exec() ) {

     success=true ;

   }
    else {
       qDebug() << "remove failed" ;
       removeQuery.lastError() ;
   }
   return success ;

}


void DBmanager::printAll() {
  qDebug()  << "People in db:"  ;
  QSqlQuery query("SELECT * FROM people") ;
  int idName=query.record().indexOf("name") ;
  while(query.next() ) {
      QString name=query.value(idName).toString() ;
      qDebug() << "===" << name ;
  }

}

void DBmanager::cmdControl() {
    do {
        QTextStream cout(stdout);
        QTextStream cin(stdin);
        QString command;

        cout << "Enter command or 'quit' to exit: ";
        cout.flush();
        command = cin.readLine().trimmed();

        if (command == "quit") {
            cout << "Exiting application." << "\n";
            break;
        } else if (command == "insert") {
            cout << "Enter data to insert: ";
            cout.flush();
            QString data = cin.readLine().trimmed();
            cout << "Data is: " << data << "\n" ;
            if (addPerson(data)) {
                cout << "Data inserted successfully." << "\n" ;
            } else {
                cout << "Failed to insert data." << "\n" ;
            }
        }
        else if(command=="print") {
            printAll() ;
        } else if(command=="remove") {
            cout << "Enter data to remove: ";
            cout.flush();
            QString data = cin.readLine().trimmed();
            removePerson(data) ;
        } else if(command=="removeAll") {
              removeAll() ;
        }
       else {
            cout << "Uknown command.Try again." << "\n" ;
        }
    } while (true);
}

DBmanager::~DBmanager() {
    if(m_db.isOpen() ) {
       m_db.close() ;
    }
}

/*void DBmanager::fillTable(QTableWidget *obj ) {
   QString dbname=QSqlDatabase(m_db).databaseName() ;
   QSqlQueryModel *model = new QSqlQueryModel;
   model->setQuery("SELECT * FROM your_table");
   obj->setModel(model);
   obj->resize(600, 400);
}*/

void DBmanager::updateTable(QTableWidget *tableWidget)
{
    tableWidget->clearContents() ;
    tableWidget->setRowCount(0) ;

    QSqlQuery query{m_db};
    query.exec("SELECT * FROM people") ;
    if (! query.exec("SELECT name FROM people")) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }


    tableWidget->setRowCount(0);

    int columnCount = query.record().count();
    tableWidget->setColumnCount(columnCount);

    for (int i = 0; i < columnCount; ++i) {
        tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(query.record().fieldName(i)));
    }

    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);
        for (int col = 0; col < columnCount; ++col) {
            tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        ++row;
    }
}
