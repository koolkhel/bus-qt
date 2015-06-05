#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>

Q_DECLARE_LOGGING_CATEGORY(TESTC)

class Test : public QObject {
	Q_OBJECT
	public:
	Test(QObject *parent = 0);
	~Test() {};
};

#endif // TEST_H
