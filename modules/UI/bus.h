#ifndef BUS_H
#define BUS_H
#include <QString>

class Bus
{
public:
    Bus();
    QString getTime() const;
    void setTime(const QString &value);

    QString getLabel() const;
    void setLabel(const QString &value);

    QString getImage() const;
    void setImage(const QString &value);

private:
    QString time;
    QString label;
    QString image;
};

#endif // BUS_H
