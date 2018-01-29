/****************************************************************************
**
** Copyright (C) 2017, 2018 Stefano Verzegnassi <stefano@ubports.com>
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
import QtQuick.Controls.Suru 2.2

Item {
    property Item control

    Rectangle {
        id: highlightRect
        width: parent.width
        height: parent.height

        visible: control.down || control.hovered || control.highlighted

        opacity: control.highlighted ? 0.5 : 1.0
        color: {
            if (control.highlighted)
                return control.Suru.highlightColor

            return control.down ? Qt.darker(control.Suru.secondaryBackgroundColor, 1.1) : control.Suru.secondaryBackgroundColor
        }

        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }

        Behavior on opacity {
            NumberAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }
    }

    Rectangle {
        width: parent.width
        height: parent.height

        visible: control.visualFocus
        color: "transparent"
        border {
            width: control.Suru.units.dp(2)
            color: control.Suru.activeFocusColor
        }
    }
}
