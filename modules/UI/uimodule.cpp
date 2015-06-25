#include "uimodule.h"
#include "skel_message.pb.h"
#include "test_message.pb.h"
#include "mainwindow.h"

#include <QApplication>


Q_LOGGING_CATEGORY(UIMODULE, "ui_module")


UIModule::UIModule(QObject *parent)
{
    //setParent(parent);
    this->name = "ui_instance";
    qCDebug(UIMODULE, "hello,world");
}

void UIModule::start()
{
    QApplication a();
    MainWindow w;
    w.show();
}

void UIModule::stop()
{

}

QStringList UIModule::getPubTopics()
{
    QStringList topics;
    topics << "uimodule_topic";
    return topics;
}


void UIModule::show()
{

}

void UIModule::getElements()
{

}

void UIModule::sendTestMessage()
{

}

void UIModule::subscribeTopic(QString topic)
{

}

void UIModule::respond(QString topic, indigo::pb::internal_msg &message)
{
    emit messageReceivedSignal();

    if (message.HasExtension(::indigo::pb::skel_message::skel_message_in)) {
        ::indigo::pb::skel_message msg = message.GetExtension(::indigo::pb::skel_message::skel_message_in);

        qCDebug(UIMODULE) << "data is: " << msg.data();
    }
}

