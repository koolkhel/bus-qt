include(../defaults.pri)

LIBS += -L../src -L../modules/protos/bin -lindigo -lindigo_message -levents_message -lgeo_message

TARGET = app
TEMPLATE = app
CONFIG += app_bundle
QT += core widgets network sql positioning
SOURCES += main.cpp

