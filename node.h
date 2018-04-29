#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QColor>

class Node : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor nodeColor READ nodeColor NOTIFY nodeColorChanged)

public:
    explicit Node(QObject *parent = nullptr);

    void setControllerIndex(int idx);

    QColor nodeColor() const;

signals:
    void nodeColorChanged();

private:
    int m_Index;
};

#endif // NODE_H
