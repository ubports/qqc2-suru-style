#ifndef QQUICKSURUUNITS_H
#define QQUICKSURUUNITS_H

#include <QtCore/qobject.h>
#include <QtGui/qfont.h>

class QQuickSuruUnits : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int breakpointXSmall READ breakpointXSmall CONSTANT)
    Q_PROPERTY(int breakpointSmall READ breakpointSmall CONSTANT)
    Q_PROPERTY(int breakpointMedium READ breakpointMedium CONSTANT)
    Q_PROPERTY(int breakpointLarge READ breakpointLarge CONSTANT)

public:
    explicit QQuickSuruUnits(QObject *parent = 0);

    // Breakpoints for responsive UI
    int breakpointXSmall() const    { return gu(56); }
    int breakpointSmall() const     { return gu(80); }
    int breakpointMedium() const    { return gu(96); }
    int breakpointLarge() const     { return gu(128); }

    // 1 rem * 0.5 = 8px. Used for convenience.
    Q_INVOKABLE int gu(qreal value) const;

    // Used for font-indipendent sizes, in px. = 1 px
    Q_INVOKABLE int dp(int value) const;

    // The size of the paragraph font, in px. = 16 px
    Q_INVOKABLE int rem(qreal value) const;
};

#endif // QQUICKSURUUNITS_H
