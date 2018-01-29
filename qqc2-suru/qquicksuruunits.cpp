#include "qquicksuruunits.h"

QQuickSuruUnits::QQuickSuruUnits(QObject *parent) : QObject(parent)
{

}

int QQuickSuruUnits::gu(qreal value) const
{
    return value * 8;
}

int QQuickSuruUnits::dp(int value) const
{
    return value;
}

int QQuickSuruUnits::rem(qreal value) const
{
    return value * 16;
}
