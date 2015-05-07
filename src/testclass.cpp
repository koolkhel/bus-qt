#include "testclass.h"

#include "nzmqt/nzmqt.hpp"
#include "indigo.pb.h"
#include <sstream>
#include <QDebug>
#include "zmq.hpp"

testclass::testclass()
{
}

bool testclass::test()
{
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
    nzmqt::ZMQContext* context = nzmqt::createDefaultContext();
    nzmqt::ZMQSocket* subscriber = context->createSocket(nzmqt::ZMQSocket::TYP_SUB);

    //subscriber->setsockopt(ZMQ_SUBSCRIBE, "", 0);

    //nzmqt::ZMQSocket* subscriber2 = context->createSocket(nzmqt::ZMQSocket::TYP_SUB);

    subscriber->connectTo("tcp://127.0.0.1:5555");
    //subscriber2->connectTo("tcp://127.0.0.1:5556");

    nzmqt::ZMQMessage message(6);

   // QList<QByteArray> messages;

    indigo_msg msg;
    msg.add_coordinates();


    /*QByteArray byteArray(msg.SerializeAsString().c_str());

    messages.insert(0,byteArray);*/

    try {

        subscriber->sendMessage(message);

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

    return true;
}
