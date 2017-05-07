#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "backendobject.h"


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


    qmlRegisterSingletonType<BackendObject>("elmsoft.rail.backendObject", 1, 0, "BackedObject", backend_provider);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
