#include "testclass.h"

#include <sstream>
#include <QDebug>
#include "zmq.hpp"

testclass::testclass(QObject* parent) : QObject(parent)
{
   /* nzmqt::ZMQContext* context = nzmqt::createDefaultContext();
    subscriber = context->createSocket(nzmqt::ZMQSocket::TYP_SUB);
    pusher = context->createSocket(nzmqt::ZMQSocket::TYP_PUSH);
    connect(subscriber,SIGNAL(messageReceived(const QList<QByteArray>&)),SLOT(messageRecieved(const QList<QByteArray>&)));*/
}

bool testclass::test()
{
   /* subscriber->subscribeTo("");
    subscriber->connectTo("tcp://127.0.0.1:5555");
    pusher->connectTo("tcp://127.0.0.1:5556");
    nzmqt::ZMQMessage message(6);

    indigo_msg msg;
    msg.add_coordinates();

    memcpy ((void *) message.data (), "Hello", 5);

    try {

        pusher->sendMessage(message.toByteArray());

    }
    catch(nzmqt::ZMQException hell)
    {
        qDebug()<<hell.what();
    }

    /*while(true)
    {
        QList<QByteArray> messages;
        messages.insert(0,QString("Hello").toLocal8Bit());
        socket->sendMessage(messages);
    }*/

    //nzmqt::ZMQSocket* recSocket = context->createSocket(nzmqt::ZMQSocket::TYP_REP);
    //nzmqt::ZMQMessage message;
    //recieveSocket->recv(&message);
    /*zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    socket.connect ("tcp://localhost:5555");

    zmq::message_t request (6);
    memcpy ((void *) request.data (), "Hello", 5);
    socket.send (request);*/

   /*for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
       zmq::message_t request (6);
       memcpy ((void *) request.data (), "Hello", 5);
       socket.send (request);

       //  Get the reply.
       zmq::message_t reply;
       socket.recv (&reply);
   }*/



    //subscriber->setsockopt(ZMQ_SUBSCRIBE, "", 0);

    //nzmqt::ZMQSocket* subscriber2 = context->createSocket(nzmqt::ZMQSocket::TYP_SUB);

    /*QByteArray byteArray(msg.SerializeAsString().c_str());

    messages.insert(0,byteArray);*/


    return true;

}


