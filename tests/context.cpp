#include "context.h"

Context* Context::pInstance = NULL;

Context::Context()
{
    context = nzmqt::createDefaultContext(this);
    context->start();
}

Context *Context::instance()
{
    if(!pInstance)
        pInstance = new Context;
    return pInstance;
}

