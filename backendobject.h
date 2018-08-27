#ifndef BACKENDOBJECT_H
#define BACKENDOBJECT_H

#include <QObject>
#include <QHash>
#include <QSignalMapper>

#include "controller.h"
#include "clientsocket.h"
#include "lever.h"
#include "jsonkeys.h"
#include "node.h"

class BackendObject : public QObject
{
    Q_OBJECT

public:
    explicit BackendObject(QObject *parent = 0);

    Q_INVOKABLE Controller* getController(const QString& key) const;
    Q_INVOKABLE Lever* getLever(const QString& key) const;
    Q_INVOKABLE Node* getNode(const QString& key) const;

    Q_INVOKABLE JsonKeys* getKeys() const;

public slots:
    void refreshControllers();
    void refreshPanel();

signals:
    void panelChanged();

private slots:
    void gotData(const QByteArray& data);
    void controllerChanged(const QString& id);
    void leverChanged(const QString& id);

private:
    void updateControllers(const QJsonObject& obj);
    void updatePanel(const QJsonObject& obj);
    void updateNodes(const QJsonObject& obj);

    void mapController(const QString& id);
    void mapLever(const QString &id);
    void mapNode(const QString &id);

    QHash<QString, Controller*> m_Controllers;
    QHash<QString, Lever*> m_Levers;
    QHash<QString, Node*> m_Nodes;

    ClientSocket* m_pSock;
    QSignalMapper* m_pControllerMap;
    QSignalMapper* m_pLeverMap;
};

#endif // BACKENDOBJECT_H
