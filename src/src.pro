#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T06:46:41
#
#-------------------------------------------------

QT       += core gui positioning network

CONFIG -= app_bundle



include(../paths.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = indigo
TEMPLATE = lib
DESTDIR=$$BINDIR

include(nzmqt/nzmqt.pri)
include(../defaults.pri)

!buildpass:system(cd ../modules/protos && ./shell.sh $$PROTODIR $$QMAKE_QMAKE)

DEFINES += _debug

SOURCES += support_unix.cpp \
    zeromqpublisher.cpp \
    zeromqsubscriber.cpp \
    dispatcher.cpp \
    module.cpp \
    modulep.cpp \
    pluginmodulefactory.cpp \
     proxy.cpp



HEADERS  += \
    zeromqpublisher.h \
    zeromqsubscriber.h \
    dispatcher.h \
    module.h \
    modulep.h \
    pluginmodulefactory.h \
    proxy.h \
    indigo.h

INCLUDEPATH += ../modules/protos/include
LIBS += -L$$PROTODIR -lsender_message -levents_message -lgeo_message

linux-g++ {
    INCLUDEPATH += /usr/local/include
    QMAKE_CXXFLAGS += -fvisibility=default -g3
    LIBS += -L/usr/local/lib -lgps -lprotobuf-lite -fvisibility=default -ldl -lbacktrace
}

linux-arm-indigo-g++ {
    LIBS += -lgps -lprotobuf-lite -ldl
}

target.path = /opt/Qt-arm
INSTALLS += target

RESOURCES +=
