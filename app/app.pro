include(../defaults.pri)

LIBS += -L../src -L../modules/protos/bin -lindigo -lsender_message -levents_message -lgeo_message

TARGET = app
TEMPLATE = app
CONFIG += app_bundle
QT += core widgets network sql positioning
SOURCES += main.cpp

DISTFILES += \
    testconfig.ini

