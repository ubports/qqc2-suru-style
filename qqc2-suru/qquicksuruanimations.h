/****************************************************************************
**
** Copyright (C) 2018 Stefano Verzegnassi <stefano@ubports.com>
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
****************************************************************************/

#ifndef QQUICKSURUANIMATIONS_H
#define QQUICKSURUANIMATIONS_H

#include <QtCore/qobject.h>
#include <QtCore/qeasingcurve.h>
#include <QtCore/qpoint.h>

class QQuickSuruAnimations : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int SnapDuration READ snapDuration CONSTANT)
    Q_PROPERTY(int FastDuration READ fastDuration CONSTANT)
    Q_PROPERTY(int BriskDuration READ briskDuration CONSTANT)
    Q_PROPERTY(int SlowDuration READ slowDuration CONSTANT)
    Q_PROPERTY(int SleepyDuration READ sleepyDuration CONSTANT)

    Q_PROPERTY(QEasingCurve EasingIn READ easingIn CONSTANT)
    Q_PROPERTY(QEasingCurve EasingOut READ easingOut CONSTANT)
    Q_PROPERTY(QEasingCurve EasingInOut READ easingInOut CONSTANT)
    Q_PROPERTY(QEasingCurve EasingOutIn READ easingOutIn CONSTANT)

public:
    explicit QQuickSuruAnimations(QObject *parent = 0);

    // https://github.com/vanilla-framework/vanilla-framework/blob/develop/scss/_settings_animations.scss
    int snapDuration() const { return 100; }
    int fastDuration() const { return 165; }
    int briskDuration() const { return 333; }
    int slowDuration() const { return 500; }
    int sleepyDuration() const { return 1000; }

    const QEasingCurve &easingIn() const { return m_easingIn; }
    const QEasingCurve &easingOut() const { return m_easingOut; }
    const QEasingCurve &easingInOut() const { return m_easingInOut; }
    const QEasingCurve &easingOutIn() const { return m_easingOutIn; }

private:
    QEasingCurve m_easingIn;
    QEasingCurve m_easingOut;
    QEasingCurve m_easingInOut;
    QEasingCurve m_easingOutIn;
};

#endif // QQUICKSURUANIMATIONS_H
