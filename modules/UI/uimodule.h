#ifndef UIMODULE_H
#define UIMODULE_H
#include "module.h"

class UiModule: public Module
{
    Q_OBJECT
public:
    UiModule(QObject *parent = 0);
    ~UiModule();

    virtual void start();
    virtual void stop();
    void show();
};

#endif // UIMODULE_H
