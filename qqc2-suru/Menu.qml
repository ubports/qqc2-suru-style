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
import QtQuick.Controls 2.2
import QtQuick.Templates 2.2 as T
import QtQuick.Controls.Suru 2.2

T.Menu {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem ? contentItem.implicitWidth + leftPadding + rightPadding : 0)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem ? contentItem.implicitHeight : 0) + topPadding + bottomPadding

    margins: control.Suru.units.gu(1)

    // Expressed in dp, since it matches background radius size
    topPadding: control.Suru.units.dp(4)
    bottomPadding: control.Suru.units.dp(4)

    transformOrigin: Item.Top

    enter: Transition {
        // grow_fade_in
        NumberAnimation { property: "scale"; from: 0.91; to: 1.0; easing: control.Suru.animations.EasingIn; duration: control.Suru.animations.FastDuration }
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; easing: control.Suru.animations.EasingIn; duration: control.Suru.animations.FastDuration }
    }

    exit: Transition {
        // fade_out
        NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; easing: control.Suru.animations.EasingIn; duration: control.Suru.animations.FastDuration }
    }

    contentItem: ListView {
        implicitHeight: contentHeight
        model: control.contentModel
        // TODO: improve this?
        interactive: ApplicationWindow.window ? contentHeight > ApplicationWindow.window.height : false
        clip: true
        keyNavigationWraps: false
        currentIndex: -1

        ScrollIndicator.vertical: ScrollIndicator {}
    }

    background: Rectangle {
        implicitWidth: control.Suru.units.gu(24)
        implicitHeight: control.Suru.units.gu(6)

        radius: control.Suru.units.dp(4)
        color: control.Suru.backgroundColor

     //   border.color: control.Suru.neutralColor
     //   border.width: 1

        layer.enabled: true
        layer.effect: ElevationEffect {
            elevation: 3
        }
    }
}
