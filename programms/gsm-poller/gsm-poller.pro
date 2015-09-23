#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T11:04:28
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = gsm-poller
CONFIG   += console
CONFIG   -= app_bundle

include(../../paths.pri)

DESTDIR=$$BINDIR

TEMPLATE = app

LIBS += -lgps
LIBS += -lpthread

SOURCES += \
    gsm-poller.cpp

HEADERS +=
