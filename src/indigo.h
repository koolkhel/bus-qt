#ifndef INDIGO_H
#define INDIGO_H

#include <QThread>
#include <stdio.h>
#define INDIGO_CHECK_THREAD do { \
       if (thread() != QThread::currentThread()) { \
            fprintf(stderr, "here should be : %p but is %p\n", thread(), QThread::currentThread());  \
            qFatal("hello\n");\
        } \
          \
       } while (0)
#endif // INDIGO_H

