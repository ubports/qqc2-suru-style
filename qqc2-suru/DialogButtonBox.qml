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
import QtQuick.Controls.Suru 2.2

T.DialogButtonBox {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)

    spacing: control.Suru.units.gu(1)
    padding: control.Suru.units.gu(2)
    topPadding: position === T.DialogButtonBox.Footer ? control.Suru.units.gu(1) : control.Suru.units.gu(2)
    bottomPadding: position === T.DialogButtonBox.Header ? control.Suru.units.gu(1) : control.Suru.units.gu(2)
    alignment: Qt.AlignRight

    delegate: Button {
        width: implicitWidth//control.count === 1 ? control.availableWidth / 2 : undefined
        highlighted: true
        flat: true
        font.capitalization: Font.AllUppercase
        font.weight: Font.Normal
    }

    contentItem: ListView {
        implicitWidth: contentWidth
        implicitHeight: control.Suru.units.gu(4)

        model: control.contentModel
        spacing: control.spacing
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        snapMode: ListView.SnapToItem
    }
}
