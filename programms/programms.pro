TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += gsm-poller

include(../paths.pri)
DESTDIR=$$BINDIR
