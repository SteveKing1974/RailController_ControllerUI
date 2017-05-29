#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
    Q_ENUMS(ControllerState)
    Q_ENUMS(ControllerDirection)

    Q_PROPERTY(double controlValue READ controlValue WRITE setControlValue NOTIFY controlValueChanged)
    Q_PROPERTY(QString controlValueText READ controlValueText NOTIFY controlValueChanged)

    Q_PROPERTY(ControllerState state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(ControllerDirection direction READ direction WRITE setDirection NOTIFY directionChanged)

    Q_PROPERTY(bool canChangeDirection READ canChangeDirection NOTIFY canChangeDirectionChanged)

public:
    explicit Controller(QObject *parent = 0);
    virtual ~Controller() {}

    enum ControllerState {
        CONTROLLER_OFF,
        CONTROLLER_ON
    } ;

    enum ControllerDirection {
        CONTROLLER_BACKWARD,
        CONTROLLER_FORWARD
    } ;

    double controlValue() const;
    QString controlValueText() const;
    void setControlValue(double newVal);

    ControllerState state() const;
    void setState(ControllerState newVal);

    ControllerDirection direction() const;
    void setDirection(ControllerDirection newVal);

    bool canChangeDirection() const;

signals:
    void stateChanged(ControllerState newValue);
    void directionChanged(ControllerDirection newValue);
    void controlValueChanged(int newValue);
    void canChangeDirectionChanged();

public slots:

private:
    int m_ControlValue;

    ControllerState m_State;
    ControllerDirection m_Direction;
};

#endif // CONTROLLER_H
