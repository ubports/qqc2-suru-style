/****************************************************************************
**
** Copyright (C) 2018 Stefano Verzegnassi <stefano@ubports.com>
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
import QtGraphicalEffects 1.0

DropShadow {
    property int elevation: 0

    //cached: true

  //  transparentBorder: true
    verticalOffset: 2

    enabled: elevation > 0

    radius: (samples - 1) * 0.5
    samples: {
        switch(elevation) {
        case 1:
            return 0
        case 2:
            return 5
        case 3:
        default:
            return 25
        }
    }

    color: {
        switch(elevation) {
        case 1:
            return "#56888888"
        case 2:
            return "#70888888"
        case 3:
        default:
            return "#62888888"
        }
    }
}
