#-------------------------------------------------
#
# Project created by QtCreator 2015-06-18T16:44:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UI
TEMPLATE = lib


SOURCES += main.cpp\
        mainwindow.cpp \
        guiwindowgraphicsobject.cpp \
        bus.cpp \
        currentbus.cpp

HEADERS  += mainwindow.h \
        guiwindowgraphicsobject.h \
        bus.h \
        currentbus.h

FORMS    += mainwindow.ui
