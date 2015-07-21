include(../../defaults.pri)

include(../plugins.pri)

TARGET = vpnremote
TEMPLATE = lib
QT -= gui

SOURCES += vpnremote.cpp \
    vpnremotepluginfactory.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -lvpnremote_message 

HEADERS += vpnremote.h \
    vpnremotepluginfactory.h

DISTFILES += \
    vpnremote.json \
    proto/vpnremote_message.proto
