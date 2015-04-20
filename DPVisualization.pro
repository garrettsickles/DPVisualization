#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T23:42:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DPVisualization
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editdistance.cpp \
    displaygrid.cpp \
    dpdisplay.cpp

HEADERS  += mainwindow.h \
    editdistance.h \
    displaygrid.h \
    dpdisplay.h

FORMS    += mainwindow.ui
