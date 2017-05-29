#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent),
    m_ControlValue(0),
    m_State(CONTROLLER_ON),
    m_Direction(CONTROLLER_FORWARD)
{

}

double Controller::controlValue() const
{
    return m_ControlValue;
}

QString Controller::controlValueText() const
{
    return QString("%1").arg(m_ControlValue);
}

void Controller::setControlValue(double newVal)
{
    const int roundVal = qRound64(newVal);
    if (m_ControlValue != roundVal)
    {
        m_ControlValue = roundVal;
        emit controlValueChanged(m_ControlValue);
        emit canChangeDirectionChanged();
    }
}

Controller::ControllerState Controller::state() const
{
    return m_State;
}

void Controller::setState(Controller::ControllerState newVal)
{
    if (newVal != m_State)
    {
        m_State = newVal;
        emit stateChanged(m_State);
    }
}

Controller::ControllerDirection Controller::direction() const
{
    return m_Direction;
}

void Controller::setDirection(Controller::ControllerDirection newVal)
{
    if (newVal != m_Direction)
    {
        m_Direction = newVal;
        emit directionChanged(m_Direction);
    }
}

bool Controller::canChangeDirection() const
{
    return (m_ControlValue == 0);
}
