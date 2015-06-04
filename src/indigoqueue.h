#pragma once

#include <QtCore/QQueue>
#include <QtCore/QByteArray>

#include "indigo_message.pb.h"

/**
	* Класс нужен для того, чтобы относительно дёшево и удобно держать очередь с необработанными
	* данными TcpSocketа/QByteArray. Заточен на char
	*
	*
	*/

#define MAXIMUM_QUEUE_SIZE 200

class IndigoOrderQueue
{
private:
    QQueue< ::indigo::pb::indigo_msg> queue;

public:
	IndigoOrderQueue(void)
	{}
	~IndigoOrderQueue(void);

    void push(::indigo::pb::indigo_msg data);
    ::indigo::pb::indigo_msg pop();
    ::indigo::pb::indigo_msg peek();
	int size();
    bool isEmpty();
};

class IndigoQueue
{
private:
	QQueue<char> queue;

public:
	IndigoQueue(void)
	{}
	~IndigoQueue(void);

	void push(char data);
	void pushAll(QByteArray &data);
    char pop();
    char peek();
	int size();
    bool isEmpty();
};
