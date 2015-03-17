#-------------------------------------------------
#
# Project created by QtCreator 2015-03-12T08:20:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    signupwindow.cpp \
    loginwindow.cpp \
    errorwindow.cpp \
    clientdata.cpp \
    listuserwindow.cpp \
    chatmenu.cpp

HEADERS  += mainwindow.h \
    signupwindow.h \
    loginwindow.h \
    errorwindow.h \
    clientdata.h \
    listuserwindow.h \
    chatmenu.h

FORMS    += mainwindow.ui \
    signupwindow.ui \
    loginwindow.ui \
    errorwindow.ui \
    listuserwindow.ui \
    chatmenu.ui
