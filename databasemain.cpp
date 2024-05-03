#include <iostream>
#include <QCoreApplication>
#include <QApplication>
#include <iostream>
#include <QString>
#include <QTextStream>
#include "dbmanagerui.h"

int main(int argc, char *argv[]) {
    using namespace std;
    QApplication a(argc, argv);

    dbmanagerUI obj ;
    obj.show() ;
    return a.exec() ;
}
