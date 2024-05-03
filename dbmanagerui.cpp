#include "dbmanagerui.h"

dbmanagerUI::dbmanagerUI(QWidget *parent)
    : QWidget(parent) , tableWidget(new QTableWidget)
{
    auto mainLayout = new QVBoxLayout(this);

    QString path = QFileDialog::getOpenFileName(nullptr, "Open Database", QDir::homePath(), "SQLite Database (*.sqlite *.db)");

    if (!path.isEmpty()) {
        try {
           database=new DBmanager(path) ;
           qDebug() << "Database opened successfully.";
        } catch (const std::invalid_argument &e) {
            qDebug() << "Error opening database:" << e.what();
        }
    } else {
        qDebug() << "No file selected.";
    }

    database->updateTable(tableWidget) ;
    mainLayout->addWidget(tableWidget);
    tableWidget->verticalHeader()->setVisible(true) ;
    QWidget *buttonContainer = new QWidget(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);


    QPushButton *addButton = new QPushButton("Add", buttonContainer);
    QPushButton *removeButton = new QPushButton("Remove", buttonContainer);
    QPushButton *removeAllButton = new QPushButton("Remove All", buttonContainer);
    QPushButton *personExistsButton= new QPushButton("Check for presence",buttonContainer);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(removeAllButton);
    buttonLayout->addWidget(personExistsButton);

    buttonContainer->setLayout(buttonLayout);


    mainLayout->addWidget(buttonContainer);

    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &dbmanagerUI::addPerson);
    connect(removeButton, &QPushButton::clicked, this, &dbmanagerUI::removePerson);
    connect(removeAllButton, &QPushButton::clicked, this, &dbmanagerUI::removeAll);
    connect(personExistsButton,&QPushButton::clicked, this, &dbmanagerUI::personExists);
}

void dbmanagerUI::addPerson() {
    QDialog *addDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(addDialog);
    QLineEdit *personNameEdit = new QLineEdit;
    personNameEdit->setPlaceholderText("Enter person to add");
    QPushButton *confirmButton = new QPushButton("Confirm");

    layout->addWidget(personNameEdit);
    layout->addWidget(confirmButton);

    addDialog->setLayout(layout);

    connect(confirmButton, &QPushButton::clicked, this, [=]() {
        auto toAdd=personNameEdit->text() ;
        database->addPerson(toAdd);
        database->updateTable(tableWidget) ;
        addDialog->close();
    }) ;
  addDialog->exec();

}

void dbmanagerUI::removePerson() {

    QDialog *removeDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(removeDialog);
    QLineEdit *personNameEdit = new QLineEdit;
    personNameEdit->setPlaceholderText("Enter person to remove");
    QPushButton *confirmButton = new QPushButton("Confirm");

    database->updateTable(tableWidget) ;

    layout->addWidget(personNameEdit);
    layout->addWidget(confirmButton);

    removeDialog->setLayout(layout);

    connect(confirmButton, &QPushButton::clicked, this, [=]() {

        if (!database->removePerson(personNameEdit->text())) {
            QMessageBox::critical(this, "Error", personNameEdit->text()+" doesn't exist in database.");
        }
        database->updateTable(tableWidget) ;
        removeDialog->close();
    });
  removeDialog->exec();
}

void dbmanagerUI::removeAll() {
    database->removeAll();
    QMessageBox::information(this,"Success","All persons are removed");
    database->updateTable(tableWidget) ;
}


void dbmanagerUI::personExists() {
    QDialog *existDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(existDialog);
    QLineEdit *personNameEdit = new QLineEdit;
    personNameEdit->setPlaceholderText("Name of person");
    QPushButton *confirmButton = new QPushButton("Confirm");

    layout->addWidget(personNameEdit);
    layout->addWidget(confirmButton);


    connect(confirmButton, &QPushButton::clicked, this, [=]() {
        auto nameToSearch=personNameEdit->text() ;
        if(database->personExists(nameToSearch) ) {
            QMessageBox::information(this,"Success","This person is present in database");
        }
        else {
            QMessageBox::information(this,"Failed","This person is NOT present in database");
         }
       existDialog->close();
    });
  existDialog->exec() ;
}
