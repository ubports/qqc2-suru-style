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
    implicitWidth: 18
    implicitHeight: 18

    property Item control

    Rectangle {
        anchors.fill: parent
        color: control.Suru.backgroundColor
        border.color: control.down
            ? control.checked ? "transparent" : control.Suru.positiveColor
            : control.checked ? control.Suru.positiveColor : control.Suru.neutralColor

        border.width: 1
        radius: 4

        scale: control.down ? 0.9 : 1.0
        Behavior on scale {
            NumberAnimation { duration: 75 }
        }

        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            scale: control.checked ? 1.0 : 0.0

            color: control.Suru.positiveColor

            Behavior on scale {
                NumberAnimation { duration: 75 }
            }
        }

        Behavior on color {
            ColorAnimation { duration: 150 }
        }

        Behavior on border.color {
            ColorAnimation { duration: 150 }
        }
    }

    Image {
        anchors { fill: parent; margins: 2 }

        source: control.checkState == Qt.PartiallyChecked
                ? "image://suru/checkmark-undefined/" + control.Suru.backgroundColor
                : "image://suru/checkmark/" + control.Suru.backgroundColor

        sourceSize.width: width
        sourceSize.height: height

        visible: control.checkState != Qt.Unchecked
    }
}
