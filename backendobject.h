#ifndef BACKENDOBJECT_H
#define BACKENDOBJECT_H

#include <QObject>
#include <QHash>
#include <QSignalMapper>

#include "controller.h"
#include "clientsocket.h"
#include "jsonkeys.h"

class BackendObject : public QObject
{
    Q_OBJECT

public:
    explicit BackendObject(QObject *parent = 0);

    Q_INVOKABLE Controller* getController(const QString& key) const;
    Q_INVOKABLE JsonKeys* getKeys() const;

public slots:
    void refreshControllers();
    void refreshPanel();

private slots:
    void gotData(const QByteArray& data);
    void controllerChanged(const QString& id);

private:
    void updateControllers(const QJsonObject& obj);
    void updatePanel(const QJsonObject& obj);
    void mapController(const QString& id);

    QHash<QString, Controller*> m_Controllers;
    ClientSocket* m_pSock;
    QSignalMapper* m_pMap;
};

#endif // BACKENDOBJECT_H
