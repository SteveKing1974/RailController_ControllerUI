#ifndef BACKENDOBJECT_H
#define BACKENDOBJECT_H

#include <QObject>
#include <QHash>

class BackendObject : public QObject
{
    Q_OBJECT

    Q_ENUMS(ControllerID)
    Q_PROPERTY(double controlValue READ controlValue WRITE setControlValue NOTIFY controlValueChanged)
    Q_PROPERTY(QString controlValueText READ controlValueText NOTIFY controlValueChanged)
    Q_PROPERTY(ControllerID currentController READ currentController WRITE setCurrentController NOTIFY currentControllerChanged)

public:
    explicit BackendObject(QObject *parent = 0);

    enum ControllerID {
        OUTER_LOOP,
        INNER_LOOP,
        STATION_OUTER,
        STATION_INNER
    } ;

    double controlValue() const;
    QString controlValueText() const;
    void setControlValue(double newVal);

    ControllerID currentController() const;
    void setCurrentController(ControllerID newVal);

signals:
    void controlValueChanged(double newValue);
    void currentControllerChanged(ControllerID newValue);

public slots:

private:
    ControllerID m_CurrentController;
    QHash<ControllerID, int> m_ControlValues;
};

#endif // BACKENDOBJECT_H
