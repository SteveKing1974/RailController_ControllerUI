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

    void setController(const QString& newVal);

    QColor nodeColor() const;

signals:
    void nodeColorChanged();

private:
    QString m_NodeController;
};

#endif // NODE_H
