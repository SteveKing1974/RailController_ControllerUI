#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "backendobject.h"
#include "controller.h"
#include "lever.h"
#include "node.h"
#include "jsonkeys.h"

static QObject *backend_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    BackendObject *beo = new BackendObject();
    return beo;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Controller>("elmsoft.rail.backendObject", 1, 0, "Controller");
    qmlRegisterType<Lever>("elmsoft.rail.backendObject", 1, 0, "Lever");
    qmlRegisterType<Node>("elmsoft.rail.backendObject", 1, 0, "Node");
    qmlRegisterUncreatableType<JsonKeys>("elmsoft.rail.backendObject", 1, 0, "JsonKeys", QLatin1String("Cannot create"));
    qmlRegisterSingletonType<BackendObject>("elmsoft.rail.backendObject", 1, 0, "BackendObject", backend_provider);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
