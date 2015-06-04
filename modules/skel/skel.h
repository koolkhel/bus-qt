#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(SKELETON)

class Skel : public Module {
	Q_OBJECT
	public:
	Skel(QObject *parent = 0);
    virtual ~Skel();
};

#endif // SKEL_H
