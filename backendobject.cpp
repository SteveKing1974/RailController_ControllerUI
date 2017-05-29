#include "backendobject.h"

BackendObject::BackendObject(QObject *parent) :
    QObject(parent)
{
    m_Controllers[OUTER_LOOP] = new Controller(this);
    m_Controllers[INNER_LOOP] = new Controller(this);
    m_Controllers[STATION_INNER] = new Controller(this);
    m_Controllers[STATION_OUTER] = new Controller(this);
}

Controller *BackendObject::getController(BackendObject::ControllerID id) const
{
    return m_Controllers[id];
}


