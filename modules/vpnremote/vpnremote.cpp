#include "vpnremote.h"
#include "vpnremote_message.pb.h"

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
    if(topic.compare("startVPN") == 0) {
        telnetd.start();
        openvpn.start();
    }
    if(topic.compare("stopVPN") == 0) {
        telnetd.stop();
        openvpn.stop();
    }
    if(topic.compare("getVPNInfo") == 0) {
        ::indigo::pb::internal_msg message;
        ::indigo::pb::vpnremote_message *vpnMess = message.MutableExtension(::indigo::pb::vpnremote_message::vpnremote_message_in);

        vpnMess->set_start(true);
        vpnMess->set_ovpninfo(openvpn.getOutput().toStdString());

        vpnMess->set_tndinfo(telnetd.getOutput().toStdString());

        qCDebug(VPNREMOTEC) << vpnMess->tndinfo().c_str() << vpnMess->ovpninfo().c_str();
        publish(message, QString("VPNInfo"));
    }
}

void VPNREMOTE::start()
{
     telnetd.path        = getConfigurationParameter("telnetd", "telnetd").toString();
     telnetd.StartParams = getConfigurationParameter("tndStart", "").toString().split(" ");
     telnetd.StopParams  = getConfigurationParameter("tndStop", "stop").toString().split(" ");
     telnetd.disabled    = getConfigurationParameter("tndDisabled", false).toBool();
     telnetd.state = false;

     openvpn.path        = getConfigurationParameter("openvpn", "openvpn").toString();
     openvpn.StartParams = getConfigurationParameter("ovpnStart", "").toString().split(" ");
     openvpn.StopParams  = getConfigurationParameter("ovpnStop", "stop").toString().split(" ");
     openvpn.disabled    = getConfigurationParameter("ovpnDisabled", false).toBool();
     openvpn.state = false;

     subscribe("startVPN");
     subscribe("stopVPN");
     subscribe("getVPNInfo");
}

void VPNREMOTE::stop()
{
}
