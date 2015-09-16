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
    uimodule.cpp \
    uipluginfactory.cpp \
    timer.cpp \
    bus.cpp \
    category.cpp

HEADERS  += mainwindow.h \
        guiwindowgraphicsobject.h \
    uimodule.h \
    uipluginfactory.h \
    timer.h \
    bus.h \
    category.h

FORMS    += mainwindow.ui

LIBS += -L../../src/ -lprotobuf-lite -lindigo -lui_message

#RESOURCES += fonts/DroidSans.ttf

#QMAKE_POST_LINK = ./compile.sh $$MODROOTDIR/UI

DISTFILES += \
    ui.json \
    proto/ui_message.proto \
    ui.rcc \
    ui.qrc
