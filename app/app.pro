include(../defaults.pri)

TARGET = app
TEMPLATE = app
CONFIG += app_bundle
QT += core widgets network sql positioning
SOURCES += main.cpp

LIBS += -L../src -lindigo
