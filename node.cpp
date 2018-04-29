#include "node.h"

#include <QHash>

static QHash<int, QColor> g_ColorTable;
Node::Node(QObject *parent) : QObject(parent)
{
    if (g_ColorTable.isEmpty())
    {
        g_ColorTable[0] = Qt::black;
        g_ColorTable[1] = Qt::blue;
        g_ColorTable[2] = Qt::magenta;
        g_ColorTable[3] = Qt::green;
        g_ColorTable[4] = Qt::red;
    }
}

void Node::setControllerIndex(int idx)
{

    if (idx != m_Index)
    {
        m_Index = idx;
        emit nodeColorChanged();
    }
}

QColor Node::nodeColor() const
{
    return g_ColorTable.value(m_Index, Qt::black);
}
