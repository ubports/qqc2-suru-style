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
import QtQuick.Controls 2.3
import QtQuick.Controls.impl 2.3
import QtQuick.Templates 2.2 as T
import QtQuick.Controls.Suru 2.2

T.ComboBox {
    id: control

    property bool useSystemFocusVisuals: true

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    spacing: control.Suru.units.gu(2)
    topPadding: control.Suru.units.gu(0.5)
    bottomPadding: control.Suru.units.gu(0.5)
    leftPadding: control.Suru.units.gu(2)
    rightPadding: control.Suru.units.gu(2)

    opacity: enabled ? 1.0 : 0.5

    delegate: ItemDelegate {
        width: control.popup.width
        height: control.Suru.units.gu(4) + control.topPadding + control.bottomPadding
        text: control.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
        highlighted: control.highlightedIndex === index
        hoverEnabled: control.hoverEnabled
    }

    indicator: ColorImage {
        x: control.mirrored ? control.leftPadding : control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2

        width: control.Suru.units.gu(2)
        height: control.Suru.units.gu(2)

        color: control.Suru.foregroundColor
        source: "qrc:/qt-project.org/imports/QtQuick/Controls.2/Suru/assets/down.png"
        sourceSize.width: width
        sourceSize.height: height
    }

    contentItem: Text {
        leftPadding: control.mirrored && control.indicator ? control.indicator.width + control.spacing : 0
        rightPadding: !control.mirrored && control.indicator ? control.indicator.width + control.spacing : 0

        text: control.displayText
        font: control.font
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

        color: control.Suru.foregroundColor
    }

    background: Rectangle {
        implicitWidth: Math.max(control.Suru.units.gu(20), parent.width * 0.45)
        implicitHeight: control.Suru.units.gu(4)

        radius: control.Suru.units.dp(4)

        border.width: control.flat ? 0 : 1

        border.color: control.pressed || popup.visible || control.visualFocus
                      ? control.Suru.highlightColor
                      : control.Suru.neutralColor

        color: control.pressed || popup.visible
               ? Qt.darker(control.Suru.secondaryBackgroundColor, 1.1)
               : control.hovered ? control.Suru.secondaryBackgroundColor : control.Suru.backgroundColor

        visible: !control.flat || control.pressed || control.hovered || control.visualFocus

        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }
    }

    popup: T.Popup {
        //y: control.height
        width: control.width
        implicitHeight: Math.min(control.Suru.units.gu(48), contentItem.implicitHeight)
        topMargin: control.Suru.units.gu(1)
        bottomMargin: control.Suru.units.gu(1)
        padding: control.Suru.units.dp(1)

        Suru.theme: control.Suru.theme

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            highlightRangeMode: ListView.ApplyRange
            highlightMoveDuration: 0

            T.ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            color: control.Suru.secondaryBackgroundColor
         //   border.color: control.Suru.neutralColor
         //   border.width: 1
            radius: control.Suru.units.dp(4)

            layer.enabled: true
            layer.effect: ElevationEffect {
                elevation: 3
            }
        }
    }
}
