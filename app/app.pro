include(../defaults.pri)

LIBS += -L../src -L../modules/protos/bin -lindigo -lsender_message -levents_message -lgeo_message

TARGET = app
TEMPLATE = app
CONFIG += app_bundle
QT += core widgets network sql positioning
SOURCES += main.cpp

DISTFILES += \
    configs\testconfig.ini \
configs\config_bb_dc.ini \
configs\config_db_wio.ini \
configs\config_power.ini    \
configs\testconfig.ini \
configs\config_bb_oh.ini   \
configs\config_dp_sy.ini   \
configs\config_sender_dl.ini \
configs\config_bb_sc.ini   \
configs\config_gps.ini     \
configs\config_sr_cn.ini \
configs\config_db_bnc.ini  \
configs\config_io.ini   \
configs\config_ui.ini \
