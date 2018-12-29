#include "node.h"

#include <QHash>
#include <jsonkeys.h>
#include <QDebug>

static QHash<QString, QColor> g_ColorTable;
Node::Node(QObject *parent) : QObject(parent), m_NodeController(QString())
{
    if (g_ColorTable.isEmpty())
    {
        g_ColorTable[JsonKeys::innerLoop()] = Qt::blue;
        g_ColorTable[JsonKeys::outerLoop()] = Qt::magenta;
        g_ColorTable[JsonKeys::stationInner()] = Qt::green;
        g_ColorTable[JsonKeys::stationOuter()] = Qt::red;
    }
}

void Node::setController(const QString& newVal)
{
    if (newVal != m_NodeController)
    {
        m_NodeController = newVal;
        emit nodeColorChanged();
    }
}

QColor Node::nodeColor() const
{
    return g_ColorTable.value(m_NodeController, Qt::black);
}
