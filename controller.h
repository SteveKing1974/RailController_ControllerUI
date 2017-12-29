#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "basecontroller.h"

class Controller : public BaseController
{
    Q_OBJECT

    Q_PROPERTY(QString controlValueText READ controlValueText NOTIFY controlTextChanged)

public:
    explicit Controller(QObject *parent = 0);
    virtual ~Controller() {}


    QString controlValueText() const;

signals:
    void controlTextChanged();

private:

};

#endif // CONTROLLER_H
