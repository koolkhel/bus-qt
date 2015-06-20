#-------------------------------------------------
#
# Project created by QtCreator 2015-06-18T16:44:09
#
#-------------------------------------------------
include(../../defaults.pri)

include(../plugins.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UI
TEMPLATE = lib


SOURCES +=\
        mainwindow.cpp \
        guiwindowgraphicsobject.cpp \
        bus.cpp \
        currentbus.cpp \
    uimodule.cpp \
    uipluginfactory.cpp

HEADERS  += mainwindow.h \
        guiwindowgraphicsobject.h \
        bus.h \
        currentbus.h \
    uimodule.h \
    uipluginfactory.h

FORMS    += mainwindow.ui

LIBS += -L../../src/ -lprotobuf-lite -lindigo -ltest_message -lskel_message -lskel_message2
