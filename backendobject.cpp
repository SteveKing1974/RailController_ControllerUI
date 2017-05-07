#include "backendobject.h"

BackendObject::BackendObject(QObject *parent) :
    QObject(parent),
    m_CurrentController(OUTER_LOOP)
{
    m_ControlValues[OUTER_LOOP] = 0;
    m_ControlValues[INNER_LOOP] = 0;
    m_ControlValues[STATION_INNER] = 0;
    m_ControlValues[STATION_OUTER] = 0;
}

double BackendObject::controlValue() const
{
    return m_ControlValues[m_CurrentController];
}

QString BackendObject::controlValueText() const
{
    return QString("%1").arg(m_ControlValues[m_CurrentController]);
}

void BackendObject::setControlValue(double newVal)
{
    const int roundVal = qRound64(newVal);
    const int curVal = m_ControlValues[m_CurrentController];
    if (curVal != roundVal)
    {
        m_ControlValues[m_CurrentController] = roundVal;
        emit controlValueChanged(roundVal);
    }
}

BackendObject::ControllerID BackendObject::currentController() const
{
    return m_CurrentController;
}

void BackendObject::setCurrentController(BackendObject::ControllerID newVal)
{
    if (m_CurrentController != newVal)
    {
        m_CurrentController = newVal;
        emit currentControllerChanged(newVal);
        emit controlValueChanged(m_ControlValues[m_CurrentController]);
    }
}
