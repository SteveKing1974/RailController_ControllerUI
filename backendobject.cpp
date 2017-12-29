#include "backendobject.h"
#include "jsonkeys.h"

#include <QJsonDocument>
#include <QJsonObject>


BackendObject::BackendObject(QObject *parent) :
    QObject(parent)
{
    m_pMap = new QSignalMapper(this);

    mapController(JsonKeys::outerLoop());
    mapController(JsonKeys::innerLoop());
    mapController(JsonKeys::stationInner());
    mapController(JsonKeys::stationOuter());

    connect(m_pMap, SIGNAL(mapped(QString)), this, SLOT(controllerChanged(QString)));
    m_pSock = new ClientSocket(this);

    connect(m_pSock, SIGNAL(dataReceived(QByteArray)), this, SLOT(gotData(QByteArray)));
}

Controller *BackendObject::getController(const QString& key) const
{
    return m_Controllers[key];
}

JsonKeys *BackendObject::getKeys() const
{
    static JsonKeys keys;
    return &keys;
}

void BackendObject::refreshControllers()
{
    QJsonObject obj;
    obj.insert(JsonKeys::command(), JsonKeys::get());
    obj.insert(JsonKeys::data(), JsonKeys::controller());
    m_pSock->sendData((QJsonDocument(obj)).toJson());
}

void BackendObject::refreshPanel()
{
    QJsonObject obj;
    obj.insert(JsonKeys::command(), JsonKeys::get());
    obj.insert(JsonKeys::data(), JsonKeys::panel());
    m_pSock->sendData((QJsonDocument(obj)).toJson());
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

void BackendObject::controllerChanged(const QString &id)
{
    QJsonObject obj;
    QJsonObject controlObj;

    obj.insert(JsonKeys::command(), JsonKeys::put());
    obj.insert(JsonKeys::data(), JsonKeys::controller());
    obj.insert(JsonKeys::controller(), id);

    controlObj = m_Controllers.value(id)->toJson();
    QJsonObject::const_iterator it = controlObj.begin();
    while (it!=controlObj.end())
    {
        obj.insert(it.key(), it.value());
        ++it;
    }
    m_pSock->sendData((QJsonDocument(obj)).toJson());
}

void BackendObject::updateControllers(const QJsonObject &obj)
{
    if (!obj.isEmpty())
    {
        const QStringList keys = obj.keys();
        foreach (const QString& k, keys)
        {
            if (m_Controllers.contains(k))
            {
                qDebug() << "Update" << k << m_Controllers.value(k)->fromJson(obj.value(k).toObject());
            }
        }
    }
}

void BackendObject::updatePanel(const QJsonObject &obj)
{
    if (!obj.isEmpty())
    {
        qDebug() << "-> updatePanel" << obj.keys();
        QJsonObject iso = obj.value(JsonKeys::isolators()).toObject();
        qDebug() << "-> " << iso.keys();
    }
}

void BackendObject::mapController(const QString &id)
{
    Controller* pCont = new Controller(this);
    connect(pCont, SIGNAL(controlValueChanged()), m_pMap, SLOT(map()));
    connect(pCont, SIGNAL(directionChanged()), m_pMap, SLOT(map()));
    connect(pCont, SIGNAL(stateChanged()), m_pMap, SLOT(map()));

    m_pMap->setMapping(pCont, id);

    m_Controllers.insert(id, pCont);
}


