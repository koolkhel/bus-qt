#include "vpnremote.h"

Q_LOGGING_CATEGORY(VPNREMOTEC, "vpnremote")

VPNREMOTE::VPNREMOTE(QObject *parent)
{
    setParent(parent);

    this->name = "vpnremote works";

    qCDebug(VPNREMOTEC, "hello,world");
}

VPNREMOTE::~VPNREMOTE()
{

}

QStringList VPNREMOTE::getPubTopics()
{
    QStringList topics;

    return topics;
}

void VPNREMOTE::respond(QString topic, indigo::pb::internal_msg &message)
{
    if(topic == startVpn) {
        telnetd.start();
        openvpn.start();
    }
    if(topic == stopVpn) {
        telnetd.stop();
        openvpn.stop();
    }
}

void VPNREMOTE::start()
{
     telnetd.path = getConfigurationParameter("telnetd", "telnetd").toString();
     telnetd.StartParams = getConfigurationParameter("tndStart", "").toString().split(" ");
     telnetd.StopParams = getConfigurationParameter("tndStop", "stop").toString().split(" ");
     telnetd.state = false;

     openvpn.path = getConfigurationParameter("openvpn", "openvpn").toString();
     openvpn.StartParams = getConfigurationParameter("ovpnStart", "").toString().split(" ");
     openvpn.StopParams = getConfigurationParameter("ovpnStop", "stop").toString().split(" ");
     openvpn.state = false;

     subscribe("startVpn");
     subscribe("stopVpn");
}

void VPNREMOTE::stop()
{
}
