#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T06:46:41
#
#-------------------------------------------------

QT       += core gui positioning network

CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = indigo
TEMPLATE = lib

include(nzmqt/nzmqt.pri)

SOURCES += gpsdpositionsource.cpp \
        gpsdsatellitesource.cpp \
        backend.cpp \
        indigoqueue.cpp \
        mainwindow.cpp \
    testclass.cpp \
    support_unix.cpp \
    indigologger.cpp \
    subscribedispatcher.cpp \
    zeromqpublisher.cpp \
    zeromqsubscriber.cpp \
    context.cpp \
    dispatcher.cpp \
    module.cpp \
    modulep.cpp \
    topic.cpp \
    pluginmodulefactory.cpp \
     proxy.cpp \



HEADERS  += mainwindow.h \
            backend.h \
            indigoqueue.h \
            gpsdpositionsource.h \
            gpsdsatellitesource.h \
    testclass.h \
    indigologger.h \
    subscribedispatcher.h \
    zeromqpublisher.h \
    zeromqsubscriber.h \
    context.h \
    dispatcher.h \
    module.h \
    modulep.h \
    topic.h \
    pluginmodulefactory.h \
    proxy.h \

    currentbus.h
FORMS    += mainwindow.ui

INCLUDEPATH += ../modules/protos/include
LIBS += -L../modules/protos/bin -lindigo_message -levents_message -lgeo_message

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
