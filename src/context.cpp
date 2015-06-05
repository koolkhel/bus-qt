#include "context.h"

Context* Context::pInstance = NULL;

Context::Context()
{
    context = new nzmqt::PollingZMQContext(this,1);
    context->start();
}

Context *Context::instance()
{
    if(!pInstance)
        pInstance = new Context;
    return pInstance;
}

void Context::stop()
{
    context->stop();
}

