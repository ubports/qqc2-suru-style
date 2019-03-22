/****************************************************************************
**
** Copyright (C) 2017, 2018 Stefano Verzegnassi <stefano@ubports.com>
** Copyright (C) 2017 The Qt Company Ltd.
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

import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.impl 2.3
import QtQuick.Templates 2.2 as T
import QtQuick.Controls.Suru 2.2

T.BusyIndicator {
    id: control

    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
    implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding

    contentItem: ColorImage {
        width: control.Suru.units.gu(12)
        height: control.Suru.units.gu(12)

        color: control.Suru.highlightColor
        source: "qrc:/qt-project.org/imports/QtQuick/Controls.2/Suru/assets/spinner.png"
        opacity: running ? 1.0 : 0.0

        RotationAnimator on rotation {
            running: control.visible && control.running
            from: 0
            to: 360
            loops: Animation.Infinite
            duration: control.Suru.animations.SleepyDuration
        }
    }
}
