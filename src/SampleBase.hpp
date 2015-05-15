#ifndef NZMQT_SAMPLEBASE_H
#define NZMQT_SAMPLEBASE_H

#include "nzmqt/nzmqt.hpp"

#include <QDebug>
#include <QEventLoop>
#include <QThread>



class SampleBase : public QObject
{
    Q_OBJECT
    typedef QObject super;

signals:
    void finished();
    void failure(const QString& what);

public slots:
    void start();
    void stop();

protected:
    SampleBase(QObject* parent);

    virtual void startImpl() = 0;

    static void sleep(unsigned long msecs);

private:
    class ThreadTools : private QThread
    {
    public:
        using QThread::msleep;

    private:
        ThreadTools() {}
    };
};

inline SampleBase::SampleBase(QObject* parent)
    : super(parent)
{
}

inline void SampleBase::start()
{
    try
    {
        startImpl();
    }
    catch (const nzmqt::ZMQException& ex)
    {
        qWarning() << Q_FUNC_INFO << "Exception:" << ex.what();
        emit failure(ex.what());
        emit finished();
    }
}

inline void SampleBase::stop()
{
    emit finished();
}

inline void SampleBase::sleep(unsigned long msecs)
{
    ThreadTools::msleep(msecs);
}



#endif // NZMQT_SAMPLEBASE_H
