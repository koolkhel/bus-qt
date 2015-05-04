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
        indigo.pb.cc \
        backend.cpp \
        indigoqueue.cpp \
        mainwindow.cpp \
    testclass.cpp \
    support_unix.cpp \
    indigologger.cpp

HEADERS  += mainwindow.h \
            backend.h \
            indigo.pb.h \
            indigoqueue.h \
            gpsdpositionsource.h \
            gpsdsatellitesource.h \
    testclass.h \
    indigologger.h

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
