#include "controller.h"

Controller::Controller(QObject *parent) : BaseController(parent)
{
    connect(this, SIGNAL(controllerUpdatedFromJson()), this, SIGNAL(controlValueChanged()));
    connect(this, SIGNAL(controllerUpdatedFromJson()), this, SIGNAL(controlTextChanged()));
    connect(this, SIGNAL(controllerUpdatedFromJson()), this, SIGNAL(stateChanged()));
    connect(this, SIGNAL(controllerUpdatedFromJson()), this, SIGNAL(directionChanged()));

    connect(this, SIGNAL(controlValueChanged()), this, SIGNAL(controlTextChanged()));
}


QString Controller::controlValueText() const
{
    return QString("%1").arg(controlValue());
}
