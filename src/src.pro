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

GP = pb
GEN_CODE = $$GP/events.pb.cc \
    $$GP/geo.pb.cc \
    $$GP/indigo.pb.cc

GEN_HED = $$GP/events.pb.h \
    $$GP/geo.pb.h \
    $$GP/indigo.pb.h

SOURCES += gpsdpositionsource.cpp \
        gpsdsatellitesource.cpp \
        backend.cpp \
        indigoqueue.cpp \
        mainwindow.cpp \
    testclass.cpp \
    support_unix.cpp \
    indigologger.cpp \
    socket.cpp \
    subscribedispatcher.cpp \
    zeromqpublisher.cpp \
    zeromqsubscriber.cpp \
    context.cpp \
    $$GEN_CODE

HEADERS  += mainwindow.h \
            backend.h \
            indigoqueue.h \
            gpsdpositionsource.h \
            gpsdsatellitesource.h \
    testclass.h \
    indigologger.h \
    socket.h \
    subscribedispatcher.h \
    Subscriber.hpp \
    Publisher.hpp \
    SampleBase.hpp \
    zeromqpublisher.h \
    zeromqsubscriber.h \
    context.h \
    $$GEN_HED

FORMS    += mainwindow.ui

OTHER_FILES += indigo.proto

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

RESOURCES += \
    indigo.qrc
