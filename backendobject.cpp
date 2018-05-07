#include "backendobject.h"
#include "jsonkeys.h"

#include <QJsonDocument>
#include <QJsonObject>


BackendObject::BackendObject(QObject *parent) :
    QObject(parent)
{
    m_pControllerMap = new QSignalMapper(this);
    m_pLeverMap = new QSignalMapper(this);

    // Controllers
    mapController(JsonKeys::outerLoop());
    mapController(JsonKeys::innerLoop());
    mapController(JsonKeys::stationInner());
    mapController(JsonKeys::stationOuter());

    // Levers
    mapLever(JsonKeys::topSidingDown());
    mapLever(JsonKeys::bottomSidingDown());
    mapLever(JsonKeys::stationSidingDown());
    mapLever(JsonKeys::topSidingUp());
    mapLever(JsonKeys::stationEntranceCrossover());
    mapLever(JsonKeys::upMainCrossover());
    mapLever(JsonKeys::downMainCrossover());
    mapLever(JsonKeys::upStationCrossover());
    mapLever(JsonKeys::downStationCrossover());
    mapLever(JsonKeys::upSiding1());
    mapLever(JsonKeys::upSiding2());
    mapLever(JsonKeys::downSiding1());
    mapLever(JsonKeys::downSiding2());


    // Nodes
    mapNode(JsonKeys::dummyOuter());
    mapNode(JsonKeys::outerRight());
    mapNode(JsonKeys::outerLeft());
    mapNode(JsonKeys::outerCenter());
    mapNode(JsonKeys::outerToInnerLeft());
    mapNode(JsonKeys::outerToInnerRight());

    mapNode(JsonKeys::dummyInner());
    mapNode(JsonKeys::innerBetweenPoints());
    mapNode(JsonKeys::innerRight());
    mapNode(JsonKeys::innerLeft());
    mapNode(JsonKeys::innerCenter());
    mapNode(JsonKeys::innerToStation());

    mapNode(JsonKeys::dummyStationOuter());
    mapNode(JsonKeys::stationOuterBetweenPoints());
    mapNode(JsonKeys::stationOuterRight());
    mapNode(JsonKeys::stationOuterLeft());
    mapNode(JsonKeys::stationOuterCenter());
    mapNode(JsonKeys::stationSidingRight1());
    mapNode(JsonKeys::dummyRightBetweenSidings());

    mapNode(JsonKeys::stationSidingRight2());
    mapNode(JsonKeys::stationSidingRight3());
    mapNode(JsonKeys::stationOuterToInnerLeft());
    mapNode(JsonKeys::stationOuterToInnerRight());

    mapNode(JsonKeys::dummyStationInner());
    mapNode(JsonKeys::stationInnerRight());
    mapNode(JsonKeys::stationInnerCenter());
    mapNode(JsonKeys::dummyLeftBetweenPoints());
    mapNode(JsonKeys::stationSidingLeft1());
    mapNode(JsonKeys::dummyLeftBetweenSidings());
    mapNode(JsonKeys::stationSidingLeft2());
    mapNode(JsonKeys::stationSidingLeft3());

    // Connect stuff
    connect(m_pControllerMap, SIGNAL(mapped(QString)), this, SLOT(controllerChanged(QString)));
    connect(m_pLeverMap, SIGNAL(mapped(QString)), this, SLOT(leverChanged(QString)));

    m_pSock = new ClientSocket(this);

    connect(m_pSock, SIGNAL(dataReceived(QByteArray)), this, SLOT(gotData(QByteArray)));
}

Controller *BackendObject::getController(const QString& key) const
{
    return m_Controllers.value(key);
}

Lever *BackendObject::getLever(const QString &key) const
{
    return m_Levers.value(key);
}

Node *BackendObject::getNode(const QString &key) const
{
    return m_Nodes.value(key);
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

void BackendObject::leverChanged(const QString &id)
{
    QJsonObject obj;

    obj.insert(JsonKeys::command(), JsonKeys::put());
    obj.insert(JsonKeys::data(), JsonKeys::panel());
    obj.insert(JsonKeys::points(), id);
    obj.insert(JsonKeys::isolators(), id);

    m_pSock->sendData((QJsonDocument(obj)).toJson());
}

void BackendObject::updateControllers(const QJsonObject &obj)
{
    if (!obj.isEmpty())
    {
        m_pControllerMap->blockSignals(true);
        const QStringList keys = obj.keys();
        foreach (const QString& k, keys)
        {
            if (m_Controllers.contains(k))
            {
                qDebug() << "Update" << k << m_Controllers.value(k)->fromJson(obj.value(k).toObject());
            }
        }
        m_pControllerMap->blockSignals(false);
    }
}

void BackendObject::updatePanel(const QJsonObject &obj)
{
    if (!obj.isEmpty())
    {
        const QJsonObject isol = obj.value(JsonKeys::isolators()).toObject();
        const QJsonObject points = obj.value(JsonKeys::points()).toObject();

        foreach (const QString& l, m_Levers.keys())
        {
            if (isol.contains(l))
            {
                m_Levers.value(l)->update(true, isol.value(l).toObject().value(JsonKeys::enabled()));
            }
            if (points.contains(l))
            {
                QJsonObject tmp = points.value(l).toObject();

                m_Levers.value(l)->update(tmp.value(JsonKeys::enabled()), tmp.value(JsonKeys::direction()));
            }
        }

//        qDebug() << "-> updatePanel" << obj.keys();
//        QJsonObject iso = obj.value(JsonKeys::points()).toObject();
//        qDebug() << "-> " << iso.keys();
//        qDebug() <<  iso.value("downmaincrossover").toObject().keys();
//        qDebug() << "-> " << iso.value("downmaincrossover").toObject().value(JsonKeys::enabled()).toBool();
    }
}

void BackendObject::mapController(const QString &id)
{
    Controller* pCont = new Controller(this);
    connect(pCont, SIGNAL(controlValueChanged()), m_pControllerMap, SLOT(map()));
    connect(pCont, SIGNAL(directionChanged()), m_pControllerMap, SLOT(map()));
    connect(pCont, SIGNAL(stateChanged()), m_pControllerMap, SLOT(map()));

    m_pControllerMap->setMapping(pCont, id);

    m_Controllers.insert(id, pCont);
}

void BackendObject::mapLever(const QString &id)
{
    Lever* pLever = new Lever(this);
    connect(pLever, SIGNAL(leverPulled()), m_pLeverMap, SLOT(map()));

    m_pLeverMap->setMapping(pLever, id);

    m_Levers.insert(id, pLever);
}

void BackendObject::mapNode(const QString &id)
{
    m_Nodes.insert(id, new Node(this));
}
