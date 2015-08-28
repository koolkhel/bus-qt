include(../defaults.pri)
#-------------------------------------------------
#
# Project created by QtCreator 2015-04-29T14:33:20
#
#-------------------------------------------------

QT       += network testlib sql widgets

TARGET = tests
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L../src -L../modules/protos/bin -L../modules/bin -ltest -ltest_message -lskel_message -lskel_message2 -lblackbox_message \
    -lindigo -lsender_message -lgeo_message -levents_message -lgtest -lprotobuf-lite -lio_message -lui_message

INCLUDEPATH += /usr/local/include
SOURCES += main.cpp \
    zeromqtests.cpp \
    dispatchertests.cpp \
    protobuftests.cpp \
    plugintests.cpp \
    gpstests.cpp \
    bboxtests.cpp \
    debouncetests.cpp \
    iotests.cpp \
    powertests.cpp \
    sendertests.cpp \
    uitests.cpp \
    sendlogtests.cpp \
    stopstests.cpp \
    vpnremotetests.cpp

#
#    loggertester.cpp \
 #   loggertests.cpp \

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    loggertester.h \
    zhelpers.h

OTHER_FILES += testconfig.ini

DISTFILES += \
    testconfig.ini
