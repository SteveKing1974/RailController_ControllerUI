#include "lever.h"
#include <QDebug>

Lever::Lever(QObject *parent) : QObject(parent), m_Enabled(true), m_Pulled(false)
{

}

void Lever::update(const QJsonValue& enabledValue, const QJsonValue& pulledValue)
{
    bool isEnabled = (enabledValue.toVariant() > 0);
    bool isPulled = (pulledValue.toVariant() > 0);

    if (isEnabled != m_Enabled)
    {
        m_Enabled =  isEnabled;
        emit enabledChanged();
    }

    m_Pulled = isPulled;
    emit pulledChanged();
}

bool Lever::enabled() const
{
    return m_Enabled;
}

bool Lever::pulled() const
{
    return m_Pulled;
}

void Lever::toggle()
{
    if (m_Enabled)
    {
        m_Pulled = !m_Pulled;
        emit leverPulled();
    }
}
