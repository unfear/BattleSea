#-------------------------------------------------
#
# Project created by QtCreator 2014-12-24T14:20:48
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = BattleSea
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    shipslist.cpp \
    seawidget.cpp \
    gamemanager.cpp \
    uimanager.cpp \
    networkmanager.cpp \
    client.cpp \
    server.cpp \
    socketapi.cpp \
    qtnetwork.cpp

HEADERS  += mainwindow.h \
    shipslist.h \
    seawidget.h \
    gamemanager.h \
    uimanager.h \
    networkmanager.h \
    networkstrategy.h \
    context.h \
    client.h \
    server.h \
    utility.h \
    socketapi.h \
    qtnetwork.h

FORMS    += mainwindow.ui

RESOURCES += \
    battlesea.qrc
