#ifndef LEVER_H
#define LEVER_H

#include <QObject>

class Lever : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)
    Q_PROPERTY(bool pulled  READ pulled NOTIFY pulledChanged)

public:
    explicit Lever(QObject *parent = nullptr);

    bool enabled() const;
    bool pulled() const;
signals:
    void enabledChanged();
    void pulledChanged();

public slots:
};

#endif // LEVER_H
