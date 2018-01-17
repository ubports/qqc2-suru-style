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

T.CheckDelegate {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    topPadding: 16
    bottomPadding: 16
    leftPadding: 16
    rightPadding: 16

    spacing: 12

    opacity: control.enabled ? 1.0 : 0.5

    indicator: CheckIndicator {
        x: text ? (control.mirrored ? control.leftPadding : control.width - width - control.rightPadding) : control.leftPadding + (control.availableWidth - width) / 2
        y: control.topPadding + (control.availableHeight - height) / 2
        control: control
    }

    contentItem: Text {
        leftPadding: !control.mirrored ? 0 : control.indicator.width + control.spacing
        rightPadding: control.mirrored ? 0 : control.indicator.width + control.spacing

        text: control.text
        font: control.font
        color: control.Suru.foregroundColor
        elide: Text.ElideRight
        visible: control.text
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        implicitHeight: 56
        color: control.Suru.backgroundColor

        Rectangle {
            anchors { left: parent.left; right: parent.right }
            anchors.bottom: parent.bottom
            height: 1
            color: control.Suru.neutralColor
        }

        HighlightRectangle {
            anchors.fill: parent
            visible: control.down || control.hovered || control.highlighted
            borderColor: control.highlighted ? control.Suru.accentColor : control.Suru.neutralColor
            backgroundColor: control.highlighted ? control.Suru.accentColor
                                                 : control.down ? Qt.darker(control.Suru.secondaryBackgroundColor, 1.1) : control.Suru.secondaryBackgroundColor
            backgroundOpacity: control.highlighted ? 0.5 : 1.0
        }
    }
}
