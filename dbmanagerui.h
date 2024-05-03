#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <memory>
#include <QTableWidget>
#include <exception>
#include <QFileDialog>
#include <QMessageBox>
#include "dbmanager.h"
#include <QHeaderView>

class dbmanagerUI : public QWidget
{
    Q_OBJECT

public:
    explicit dbmanagerUI(QWidget *parent = nullptr);
    void addPerson() ;
    void removePerson() ;
    void removeAll() ;
    void personExists() ;
private:
    DBmanager* database ;
    QTableWidget *tableWidget ;
};

