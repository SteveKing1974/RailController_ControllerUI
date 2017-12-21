#ifndef BACKENDOBJECT_H
#define BACKENDOBJECT_H

#include <QObject>
#include <QHash>

#include "controller.h"
#include "clientsocket.h"

class BackendObject : public QObject
{
    Q_OBJECT

//    Q_ENUMS(ControllerID)

public:
    explicit BackendObject(QObject *parent = 0);

    enum ControllerID {
        OUTER_LOOP,
        INNER_LOOP,
        STATION_OUTER,
        STATION_INNER
    } ;

    Q_INVOKABLE Controller* getController(ControllerID id) const;

public slots:
    void refreshControllers();

protected:
    void timerEvent(QTimerEvent *);

private slots:
    void gotData(const QByteArray& data);

private:
    void updateControllers(const QJsonObject& obj);
    void updatePanel(const QJsonObject& obj);

    QHash<ControllerID, Controller*> m_Controllers;
    ClientSocket* m_pSock;
};

#endif // BACKENDOBJECT_H
