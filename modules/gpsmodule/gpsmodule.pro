include(../../defaults.pri)

include(../plugins.pri)

TARGET = gpsmodule
TEMPLATE = lib
QT -= gui
QT += positioning

SOURCES += gpsmodule.cpp \
    gpsmodulepluginfactory.cpp \
    gpsdpositionsource.cpp \
    gpsdsatellitesource.cpp
LIBS += -L../../src/ -lgps -lprotobuf-lite -lindigo -lgpsmodule_message

HEADERS += gpsmodule.h \
    gpsmodulepluginfactory.h \
    gpsdpositionsource.h \
    gpsdsatellitesource.h

DISTFILES += \
    gpsmodule.json \
    proto/gpsmodule_message.proto \
    proto/geo_message.proto
