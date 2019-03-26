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

T.BusyIndicator {
    id: control

    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
    implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding

    contentItem: Image {
        id: image
        width: control.Suru.units.gu(6)
        height: control.Suru.units.gu(6)

        sourceSize.width: control.Suru.units.gu(6)
        sourceSize.height: control.Suru.units.gu(6)

        source: "qrc:/qt-project.org/imports/QtQuick/Controls.2/Suru/assets/spinner.svg"
        opacity: running ? 1.0 : 0.0

        RotationAnimator on rotation {
            running: control.visible && control.running
            from: 0
            to: 360
            loops: Animation.Infinite
            duration: control.Suru.animations.SleepyDuration
        }

        ShaderEffect {
            id: colorizedImage
            objectName: "shader"

            anchors.fill: parent
            visible: image.status == Image.Ready

            property Image source: image
            property color keyColorOut: control.Suru.highlightColor
            property color keyColorIn: "#808080"
            property real threshold: 0.1

            fragmentShader: "
                varying highp vec2 qt_TexCoord0;
                uniform sampler2D source;
                uniform highp vec4 keyColorOut;
                uniform highp vec4 keyColorIn;
                uniform lowp float threshold;
                uniform lowp float qt_Opacity;
                void main() {
                    lowp vec4 sourceColor = texture2D(source, qt_TexCoord0);
                    gl_FragColor = mix(keyColorOut * vec4(sourceColor.a), sourceColor, step(threshold, distance(sourceColor.rgb / sourceColor.a, keyColorIn.rgb))) * qt_Opacity;
                }"
        }
    }
}
