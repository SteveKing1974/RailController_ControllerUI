#ifndef BACKENDOBJECT_H
#define BACKENDOBJECT_H

#include <QObject>
#include <QHash>

#include "controller.h"

class BackendObject : public QObject
{
    Q_OBJECT

    Q_ENUMS(ControllerID)

public:
    explicit BackendObject(QObject *parent = 0);

    enum ControllerID {
        OUTER_LOOP,
        INNER_LOOP,
        STATION_OUTER,
        STATION_INNER
    } ;

    Q_INVOKABLE Controller* getController(ControllerID id) const;

public slots:

private:
    QHash<ControllerID, Controller*> m_Controllers;
};

#endif // BACKENDOBJECT_H
