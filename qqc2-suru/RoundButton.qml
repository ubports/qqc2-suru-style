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
import QtQuick.Templates 2.2 as T
import QtQuick.Controls.Suru 2.2

// TODO: highlighted/checked visuals for flat button style

T.RoundButton {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: control.Suru.units.gu(2)

    property bool useSystemFocusVisuals: true

    opacity: enabled ? 1.0 : 0.5

    contentItem: Text {
        text: control.text
        font: control.font
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: control.flat && control.highlighted ? control.Suru.highlightColor
                                                   : !control.flat && control.highlighted ? control.Suru.backgroundColor : control.Suru.foregroundColor

    }

    background: Rectangle {
        implicitWidth: control.Suru.units.gu(6)
        implicitHeight: control.Suru.units.gu(6)
        radius: control.radius

        property color __normalColor: (control.highlighted || control.checked) && !control.flat ? control.Suru.highlightColor : control.Suru.backgroundColor

        color: control.down ? Qt.darker(__normalColor, 1.2)
                            : control.hovered ? Qt.darker(__normalColor, 1.1) : __normalColor
        border.width: !control.flat && (control.highlighted || control.checked) ? 0 : 1
        border.color: control.Suru.neutralColor

        layer.enabled: !control.flat
        layer.effect: ElevationEffect {
            elevation: !control.down ? 2 : 3
        }

        ColorAnimation {
            duration: control.Suru.animations.FastDuration
            easing: control.Suru.animations.EasingIn
        }
    }
}
