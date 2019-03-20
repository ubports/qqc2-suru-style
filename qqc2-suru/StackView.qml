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

T.StackView {
    id: control

    popEnter: Transition {
        NumberAnimation { property: "opacity"; from: 0; to: 1; duration: control.Suru.animations.FastDuration; easing: control.Suru.animations.EasingOut }
    }

    popExit: Transition {
        NumberAnimation { property: "opacity"; from: 1; to: 0; duration: control.Suru.animations.FastDuration; easing: control.Suru.animations.EasingIn }
    }

    pushEnter: Transition {
        NumberAnimation { property: "opacity"; from: 0; to: 1; duration: control.Suru.animations.FastDuration; easing: control.Suru.animations.EasingOut }
    }

    pushExit: Transition {
        NumberAnimation { property: "opacity"; from: 1; to: 0; duration: control.Suru.animations.FastDuration; easing: control.Suru.animations.EasingIn }
    }

    replaceEnter: Transition {
        NumberAnimation { property: "opacity"; from: 0; to: 1; duration: control.Suru.animations.FastDuration; easing: control.Suru.animations.EasingOut }
    }

    replaceExit: Transition {
        NumberAnimation { property: "opacity"; from: 1; to: 0; duration: control.Suru.animations.FastDuration; easing: control.Suru.animations.EasingIn }
    }
}
