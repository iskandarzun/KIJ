#-------------------------------------------------
#
# Project created by QtCreator 2015-03-21T02:12:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatClientVer2
TEMPLATE = app


SOURCES += main.cpp\
        menuwindow.cpp \
    connection.cpp \
    clientdata.cpp

HEADERS  += menuwindow.h \
    connection.h \
    clientdata.h

FORMS    += menuwindow.ui
