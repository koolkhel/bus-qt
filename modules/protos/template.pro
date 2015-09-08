include(../../../defaults.pri)

linux-g++ {
	INCLUDEPATH += /usr/local/include
	QMAKE_CXXFLAGS += -fvisibility=default -g3
	LIBS += -L/usr/local/lib -lgps -lprotobuf-lite -fvisibility=default -ldl -lbacktrace
}

linux-arm-indigo-g++ {
	LIBS += -lgps -lprotobuf-lite -ldl
}


TARGET = CLASS
TEMPLATE = lib

SOURCES += CLASS.pb.cc

HEADERS += CLASS.pb.h
