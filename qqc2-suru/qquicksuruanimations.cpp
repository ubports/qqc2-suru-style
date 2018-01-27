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

#include "qquicksuruanimations.h"

QQuickSuruAnimations::QQuickSuruAnimations(QObject *parent)
    : QObject(parent)
{
    m_easingIn = QEasingCurve(QEasingCurve::BezierSpline);
    m_easingIn.addCubicBezierSegment(QPointF(.55, .055), QPointF(.675, .19), QPointF(1, 1));

    m_easingOut = QEasingCurve(QEasingCurve::BezierSpline);
    m_easingOut.addCubicBezierSegment(QPointF(.215, .61), QPointF(.355, 1), QPointF(1, 1));

    // As composition of m_easingIn and m_easingOut
    m_easingInOut = QEasingCurve(QEasingCurve::BezierSpline);
    m_easingInOut.addCubicBezierSegment(QPointF(.215, .055), QPointF(.355, .19), QPointF(.5, .5));
    m_easingInOut.addCubicBezierSegment(QPointF(.55, .61), QPointF(.675, 1), QPointF(1, 1));

    // As composition of m_easingIn and m_easingOut
    m_easingOutIn = QEasingCurve(QEasingCurve::BezierSpline);
    m_easingOutIn.addCubicBezierSegment(QPointF(.055, .215), QPointF(.19, .355), QPointF(.5, .5));
    m_easingOutIn.addCubicBezierSegment(QPointF(.61, .55), QPointF(1, .675), QPointF(1, 1));
}
