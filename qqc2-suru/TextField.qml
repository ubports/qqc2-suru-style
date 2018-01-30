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
import QtQuick.Controls 2.2
import QtQuick.Controls.impl 2.2
import QtQuick.Controls.Suru 2.2

T.TextField {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            placeholderText ? placeholder.implicitWidth + leftPadding + rightPadding : 0)
                            || contentWidth + leftPadding + rightPadding
    implicitHeight: Math.max(contentHeight + topPadding + bottomPadding,
                             background ? background.implicitHeight : 0,
                             placeholder.implicitHeight + topPadding + bottomPadding)

    leftPadding: control.Suru.units.gu(1.5)
    rightPadding: control.Suru.units.gu(1.5)
    topPadding: control.Suru.units.gu(1)
    bottomPadding: control.Suru.units.gu(1)

    opacity: control.enabled ? 1.0 : 0.5

    color: control.Suru.foregroundColor
    selectionColor: Suru.highlightColor
    selectedTextColor: "white"
    verticalAlignment: TextInput.AlignVCenter

    cursorDelegate: CursorDelegate { }

    PlaceholderText {
        id: placeholder
        x: control.leftPadding
        y: control.topPadding
        width: control.width - (control.leftPadding + control.rightPadding)
        height: control.height - (control.topPadding + control.bottomPadding)

        text: control.placeholderText
        font: control.font
        color: Suru.foregroundColor
        opacity: control.activeFocus ? 0.8 : 0.6
        visible: !control.length && !control.preeditText && (!control.activeFocus || control.horizontalAlignment !== Qt.AlignHCenter)
        verticalAlignment: control.verticalAlignment
        elide: Text.ElideRight
        Suru.textLevel: Suru.SecondaryText
    }

    background: Rectangle {
        implicitWidth: control.Suru.units.gu(24)
        implicitHeight: control.Suru.units.gu(4)

        radius: control.Suru.units.dp(4)
        border.width: control.Suru.units.dp(1)
        border.color: control.activeFocus
                      ? control.Suru.activeFocusColor
                      : control.Suru.neutralColor

        color: control.hovered && !control.activeFocus ? control.Suru.secondaryBackgroundColor
                                                       : control.down ? Qt.darker(control.Suru.secondaryBackgroundColor, 1.1) : control.Suru.backgroundColor

        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }
    }
}
