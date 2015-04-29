include(../defaults.pri)
#-------------------------------------------------
#
# Project created by QtCreator 2015-04-29T14:33:20
#
#-------------------------------------------------

QT       += testlib

TARGET = tests
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L../src -lindigo -lgtest

INCLUDEPATH += /usr/local/include
SOURCES += main.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
