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

LIBS += -L../src -lindigo -lindigo_message -lgeo_message -levents_message -lgtest -lprotobuf-lite

INCLUDEPATH += /usr/local/include
SOURCES += main.cpp \
    loggertester.cpp \
    zeromqpublisher.cpp \
    zeromqsubscriber.cpp \
    loggertests.cpp \
    zeromqtests.cpp \
    dispatchertests.cpp \
    protobuftests.cpp \
    gpsmodule.cpp \
    testmodule.cpp \
    proxy.cpp \
    plugintests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    loggertester.h \
    zeromqpublisher.h \
    zeromqsubscriber.h \
    zhelpers.h \
    gpsmodule.h \
    testmodule.h \
    proxy.h

OTHER_FILES += testconfig.ini

DISTFILES += \
    testconfig.ini
