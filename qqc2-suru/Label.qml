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

T.Label {
    id: control

    opacity: enabled ? 1.0 : 0.5
    color: control.Suru.foregroundColor
    linkColor: control.Suru.highlightColor

    font: {
        switch (control.Suru.textLevel) {
        case Suru.HeadingOne:
            return control.Suru.units.fontHeadingOne
        case Suru.HeadingTwo:
            return control.Suru.units.fontHeadingTwo
        case Suru.HeadingThree:
            return control.Suru.units.fontHeadingThree
        case Suru.Paragraph:
            return control.Suru.units.fontParagraph
        case Suru.Small:
            return control.Suru.units.fontSmall
        case Suru.Caption:
            return control.Suru.units.fontCaption
        case Suru.CodeBlock:
            return control.Suru.units.fontCodeBlock

        default:
            return control.Suru.units.fontParagraph
        }
    }
}
