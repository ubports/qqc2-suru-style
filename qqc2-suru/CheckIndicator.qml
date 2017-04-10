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
import QtQuick.Controls 2.3
import QtQuick.Controls.impl 2.3
import QtQuick.Controls.Suru 2.2

Item {
    implicitWidth: control.Suru.units.gu(2.5)
    implicitHeight: control.Suru.units.gu(2.5)

    property Item control

    Rectangle {
        anchors.fill: parent
        color: control.Suru.backgroundColor
        border.color: control.down
            ? control.checked ? "transparent" : control.Suru.highlightColor
            : control.checked ? control.Suru.highlightColor : control.Suru.neutralColor

        border.width: 1
        radius: 4

        scale: control.down ? 0.91 : 1.0

        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            scale: control.checked ? 1.0 : 0.0

            color: control.Suru.highlightColor

            Behavior on scale {
                NumberAnimation {
                    duration: control.Suru.animations.SnapDuration
                    easing: control.down
                            ? control.Suru.animations.EasingIn
                            : control.Suru.animations.EasingOut
                }
            }
        }

        Behavior on scale {
            NumberAnimation {
                duration: control.Suru.animations.SnapDuration
                easing: control.down
                        ? control.Suru.animations.EasingIn
                        : control.Suru.animations.EasingOut
            }
        }

        Behavior on border.color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.down || control.checked
                        ? control.Suru.animations.EasingIn
                        : control.Suru.animations.EasingOut
            }
        }
    }

    ColorImage {
        anchors { fill: parent; margins: control.Suru.units.dp(2) }

        color: control.Suru.backgroundColor
        source: "qrc:/qt-project.org/imports/QtQuick/Controls.2/Suru/assets/" + (control.checkState == Qt.PartiallyChecked ? "checkmark-undefined" : "checkmark") + ".png"

        sourceSize.width: width
        sourceSize.height: height

        visible: control.checkState != Qt.Unchecked
    }
}
