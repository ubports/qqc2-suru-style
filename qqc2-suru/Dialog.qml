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
import QtQuick.Controls 2.5
import QtQuick.Controls.Suru 2.5
import QtQuick.Templates 2.5 as T
import "impl"

T.Dialog {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            header && header.visible ? header.implicitWidth : 0,
                            footer && footer.visible ? footer.implicitWidth : 0,
                            contentWidth > 0 ? contentWidth + leftPadding + rightPadding : 0)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             (header && header.visible ? header.implicitHeight + spacing : 0)
                              + (footer && footer.visible ? footer.implicitHeight + spacing : 0)
                              + (contentHeight > 0 ? contentHeight + topPadding + bottomPadding : 0))

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)


    leftPadding: control.Suru.units.gu(2)
    rightPadding: control.Suru.units.gu(2)
    topPadding: control.Suru.units.gu(1)
    bottomPadding: control.Suru.units.gu(1)

    enter: Transition {
        // grow_fade_in
        NumberAnimation { property: "scale"; from: 0.91; to: 1.0; easing: control.Suru.animations.EasingIn; duration: control.Suru.animations.SnapDuration }
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; easing: control.Suru.animations.EasingIn; duration: control.Suru.animations.SnapDuration }
    }

    exit: Transition {
        // fade_out
        NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; easing: control.Suru.animations.EasingIn; duration: control.Suru.animations.SnapDuration }
    }

    background: Rectangle {
        color: control.Suru.backgroundColor
        radius: control.Suru.units.dp(4)
       // border.width: 1
      //  border.color: control.Suru.neutralColor

        layer.enabled: true
        layer.effect: ElevationEffect {
            elevation: 3
        }
    }

    header: Label {
        text: control.title
        visible: control.title
        elide: Label.ElideRight
        topPadding: control.Suru.units.gu(3)
        leftPadding: control.Suru.units.gu(2)
        rightPadding: control.Suru.units.gu(2)

        Suru.textLevel: Suru.HeadingThree
        Suru.textStyle: Suru.PrimaryText
    }

    footer: DialogButtonBox {
        visible: count > 0
    }
}
