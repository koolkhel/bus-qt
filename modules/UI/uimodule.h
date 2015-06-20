#ifndef UIMODULE_H
#define UIMODULE_H
#include "module.h"

class UiModule: public Module
{
    Q_OBJECT
public:
    UiModule(QObject *parent = 0);
    virtual ~UiModule() {};

    void start();
    void stop();
    void show();
    virtual QStringList getPubTopics();

public slots:
    virtual void respond(indigo::pb::internal_msg &message);
};

#endif // UIMODULE_H
