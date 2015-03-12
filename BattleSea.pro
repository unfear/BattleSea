#-------------------------------------------------
#
# Project created by QtCreator 2014-12-24T14:20:48
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = BattleSea
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    shipslist.cpp \
    seawidget.cpp \
    gamemanager.cpp \
    uimanager.cpp \
    networkmanager.cpp

HEADERS  += mainwindow.h \
    shipslist.h \
    seawidget.h \
    gamemanager.h \
    uimanager.h \
    networkmanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    battlesea.qrc
