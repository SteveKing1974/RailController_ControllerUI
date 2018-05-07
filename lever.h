#ifndef LEVER_H
#define LEVER_H

#include <QObject>
#include <QJsonValue>

class Lever : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)
    Q_PROPERTY(bool pulled  READ pulled NOTIFY pulledChanged)

public:
    explicit Lever(QObject *parent = nullptr);

    void update(const QJsonValue& enabledValue, const QJsonValue& pulledValue);

    bool enabled() const;
    bool pulled() const;

public slots:
    void toggle();

signals:
    void enabledChanged();
    void pulledChanged();
    void leverPulled();

private:
    bool m_Enabled;
    bool m_Pulled;
};

#endif // LEVER_H
