#include "stops.h"
#include <algorithm>

#include "geo_message.pb.h"

Q_LOGGING_CATEGORY(STOPSC, "stops")

STOPS::STOPS(QObject *parent)
{
    setParent(parent);

    this->name = "stops works";

    stopTopic = "stoped";

    qCDebug(STOPSC, "hello,world");
}

STOPS::~STOPS()
{

}

QStringList STOPS::getPubTopics()
{
    QStringList topics;

    topics << stopTopic;

    return topics;
}

void STOPS::respond(QString topic, indigo::pb::internal_msg &message)
{
    qCDebug(STOPSC) << topic;
    if (message.HasExtension(::indigo::pb::indigo_geo::geo_coords_in)) {
        ::indigo::pb::indigo_geo msg = message.GetExtension(::indigo::pb::indigo_geo::geo_coords_in);
        if(steps.size() == storedSteps) {
            std::rotate(steps.begin(), steps.begin() + 1, steps.end());
            steps[storedSteps - 1] = (qMakePair(msg.longitude(), msg.latitude()));
            if(check(msg.speed_kmh())) {
                ::indigo::pb::internal_msg message;
                publish(message, stopTopic);
            }
        } else {
            steps.push_back(qMakePair(msg.longitude(), msg.latitude()));
        }
    }
}

bool STOPS::check(int sc)
{
    if(typeOfLogic) {
        int maxLat = steps[0].first, maxLot = steps[0].second,
            minLat = steps[0].first, minLot = steps[0].second;
        for(int i = 1; i < steps.size(); ++i) {
            maxLat = qMax(maxLat, steps[i].first);
            maxLot = qMax(maxLot, steps[i].second);
            minLat = qMin(minLat, steps[i].first);
            minLot = qMin(minLot, steps[i].second);
        }

        return ((maxLat - minLat < accuracy ) && (maxLot - minLot < accuracy));
    } else {
        return (sc < accuracy);
    }
}

void STOPS::start()
{
    storedSteps = getConfigurationParameter("storedSteps", 3).toInt();
    typeOfLogic = getConfigurationParameter("typeOfLogic", 1).toInt();
    stopTopic   = getConfigurationParameter("stopTopic", "stoped").toString();
    accuracy    = getConfigurationParameter("accuracy", 100).toInt();

    QStringList topics = getConfigurationParameter("inputTopics", "").toStringList();

    foreach (QString topic, topics) {
        subscribe(topic);
    }

}

void STOPS::stop()
{
}
