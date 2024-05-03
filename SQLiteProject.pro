CONFIG += c++11 console
CONFIG -= app_bundle
QT+=sql \
    widgets \
    core gui

SOURCES += \
        dbmanager.cpp \
        dbmanagerui.cpp \
        main.cpp

HEADERS += \
    dbmanager.h \
    dbmanagerui.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

