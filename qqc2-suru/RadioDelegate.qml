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
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Controls.Suru 2.2
import QtQuick.Templates 2.12 as T
import "impl"

T.RadioDelegate {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    topPadding: control.Suru.units.gu(2)
    bottomPadding: control.Suru.units.gu(2)
    leftPadding: control.Suru.units.gu(2)
    rightPadding: control.Suru.units.gu(2)

    spacing: control.Suru.units.gu(1.5)

    opacity: control.enabled ? 1.0 : 0.5

    icon.width: 24
    icon.height: 24
    icon.color: control.Suru.foregroundColor

    contentItem: IconLabel {
        leftPadding: !control.mirrored ? 0 : control.indicator.width + control.spacing
        rightPadding: control.mirrored ? 0 : control.indicator.width + control.spacing

        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display
        alignment: control.display === IconLabel.IconOnly || control.display === IconLabel.TextUnderIcon ? Qt.AlignCenter : Qt.AlignLeft

        icon: control.icon
        text: control.text
        font: control.font
        color: control.Suru.foregroundColor
    }

    indicator: RadioIndicator {
        x: control.mirrored ? control.leftPadding : control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2

        control: control
    }

    background: Rectangle {
        implicitHeight: control.Suru.units.gu(7)
        color: control.Suru.backgroundColor

        HighlightFocusRectangle {
            control: control
            width: parent.width
            height: parent.height
        }

        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: control.Suru.units.dp(1)
            color: control.Suru.neutralColor
        }
    }
}
