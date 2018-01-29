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

T.ApplicationWindow {
    id: window

    color: window.Suru.backgroundColor

    overlay.modal: Rectangle {
        color: window.Suru.overlayColor
        Behavior on opacity { NumberAnimation { duration: window.Suru.animations.FastDuration } }
    }

    overlay.modeless: Rectangle {
        color: window.Suru.overlayColor
        Behavior on opacity { NumberAnimation { duration: window.Suru.animations.FastDuration } }
    }

    Rectangle {
        parent: window.activeFocusControl
        anchors.centerIn: parent
        width: parent ? parent.width + (window.Suru.units.dp(4) * 2) : 0
        height: parent ? parent.height + 8 : 0
        visible: parent && !!parent.useSystemFocusVisuals && !!parent.visualFocus

        color: "transparent"
        border {
            width: window.Suru.units.dp(2)
            color: window.Suru.activeFocusColor
        }
    }
}
