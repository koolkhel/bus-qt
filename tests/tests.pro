include(../defaults.pri)
#-------------------------------------------------
#
# Project created by QtCreator 2015-04-29T14:33:20
#
#-------------------------------------------------

QT       += network testlib

TARGET = tests
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L../src -lindigo -lgtest

INCLUDEPATH += /usr/local/include
SOURCES += main.cpp \
    loggertester.cpp \
    zeromqpublisher.cpp \
    zeromqsubscriber.cpp \
    context.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    loggertester.h \
    zeromqpublisher.h \
    zeromqsubscriber.h \
    context.h
