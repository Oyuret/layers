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
    src/mygraphicsview.cpp \
    src/abstract_node.cpp \
    src/node.cpp \
    src/algorithm.cpp \
    src/graph.cpp \
    src/xml_parser.cpp \
    src/cfg.cpp \
    src/abstract_edge.cpp \
    src/edgeitem.cpp \
    src/cyclereduction.cpp \
    src/assignlayers.cpp \
    src/insertdummynodes.cpp \
    src/dummynode.cpp \
    src/reducecrossings.cpp

HEADERS  += include/blockitem.h \
    include/mainwindow.h \
    include/mygraphicsview.h \
    include/abstract_node.h \
    include/node.h \
    include/algorithm.h \
    include/graph.h \
    include/xml_parser.h \
    include/cfg.h \
    include/abstract_edge.h \
    include/edgeitem.h \
    include/cyclereduction.h \
    include/assignlayers.h \
    include/insertdummynodes.h \
    include/dummynode.h \
    include/reducecrossings.h

FORMS    += ui/mainwindow.ui

CONFIG += c++11

INCLUDEPATH += include
