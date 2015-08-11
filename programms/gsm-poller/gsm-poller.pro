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

TEMPLATE = app

LIBS += -lgps
LIBS += -lpthread

SOURCES += main.cpp \
    gps-indigo.cpp
HEADERS += gps-indigo.h
