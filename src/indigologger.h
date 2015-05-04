#ifndef INDIGOLOGGER_H
#define INDIGOLOGGER_H

#include <QtNetwork/QUdpSocket>

class IndigoLogger;

#define ISL_DEBUG(str) IndigoLogger::getInstance()->log(IndigoLogger::DEBUG, str)
#define ISL_ERROR(str) IndigoLogger::getInstance()->log(IndigoLogger::ERROR, str)

class IndigoLogger
{
public:
    enum {
        PORT = 45000
    };
    enum LogLevel {
        // сюда идет все
        DEBUG = 2,
        // несбывшиеся предположения по поводу работы кода
        ERROR = 4,
    };

    IndigoLogger();

    static IndigoLogger *getInstance() {
        if (instance == NULL)
            instance = new IndigoLogger();
        return instance;
    }

    inline QString getLevelTag(int logLevel);

    void log(int logLevel, QString str);
private:
    QUdpSocket *socket;

    static IndigoLogger *instance;
};

#endif // INDIGOLOGGER_H
