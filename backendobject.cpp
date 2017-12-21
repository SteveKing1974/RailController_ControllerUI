#include "backendobject.h"
#include "jsonkeys.h"

#include <QJsonDocument>
#include <QJsonObject>

BackendObject::BackendObject(QObject *parent) :
    QObject(parent)
{
    m_Controllers[OUTER_LOOP] = new Controller(this);
    m_Controllers[INNER_LOOP] = new Controller(this);
    m_Controllers[STATION_INNER] = new Controller(this);
    m_Controllers[STATION_OUTER] = new Controller(this);

    m_pSock = new ClientSocket(this);

    connect(m_pSock, SIGNAL(dataReceived(QByteArray)), this, SLOT(gotData(QByteArray)));
    //startTimer(2000);
}

Controller *BackendObject::getController(BackendObject::ControllerID id) const
{
    return m_Controllers[id];
}

void BackendObject::refreshControllers()
{
    m_pSock->sendData((JsonKeys::get() + JsonKeys::seperator() + JsonKeys::controller()).toLatin1());
}

void BackendObject::timerEvent(QTimerEvent*)
{
    //m_pSock->sendData("get:panel");
}

void BackendObject::gotData(const QByteArray &data)
{
    QJsonParseError err;
    QJsonObject obj = QJsonDocument::fromJson(data, &err).object();

    if (err.error == QJsonParseError::NoError )
    {
        qDebug() << "Got" << obj.keys();
        updateControllers(obj.value(JsonKeys::controller()).toObject());
        updatePanel(obj.value(JsonKeys::panel()).toObject());
    }
    else
    {
        qDebug() << "Parse error" << err.errorString();;
    }

}

void BackendObject::updateControllers(const QJsonObject &obj)
{
    if (!obj.isEmpty())
    {
        qDebug() << "-> updateControllers" << obj.value("innerloop").toObject().keys();
    }
}

void BackendObject::updatePanel(const QJsonObject &obj)
{
    if (!obj.isEmpty())
    {
        qDebug() << "-> updatePanel" << obj.keys();
    }
}


