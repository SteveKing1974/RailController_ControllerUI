#ifndef BACKENDOBJECT_H
#define BACKENDOBJECT_H

#include <QObject>

class BackendObject : public QObject
{
    Q_OBJECT
public:
    explicit BackendObject(QObject *parent = 0);

signals:

public slots:
};

#endif // BACKENDOBJECT_H