#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T18:18:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = layers
TEMPLATE = app


SOURCES += src/blockitem.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mygraphicsview.cpp

HEADERS  += include/blockitem.h \
    include/mainwindow.h \
    include/mygraphicsview.h

FORMS    += ui/mainwindow.ui

CONFIG += c++11

INCLUDEPATH += include
