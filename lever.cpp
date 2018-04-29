#include "lever.h"

Lever::Lever(QObject *parent) : QObject(parent)
{

}

bool Lever::enabled() const
{
    return false;
}

bool Lever::pulled() const
{
    return false;
}
