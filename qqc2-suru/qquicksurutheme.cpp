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

#include "qquicksurutheme_p.h"
#include "qquicksuruunits.h"

QQuickSuruTheme::QQuickSuruTheme(QPlatformTheme *theme)
    : QQuickProxyTheme(theme)
{
    m_suruUnits = new QQuickSuruUnits();
}

const QFont *QQuickSuruTheme::font(QPlatformTheme::Font type) const
{
    switch (type) {
    case QPlatformTheme::GroupBoxTitleFont:
        return &m_suruUnits->fontSmall();
    case QPlatformTheme::ComboMenuItemFont:
    case QPlatformTheme::TipLabelFont:
    case QPlatformTheme::TabButtonFont:
    case QPlatformTheme::SystemFont:
    case QPlatformTheme::MenuFont:
    case QPlatformTheme::MenuBarFont:
    case QPlatformTheme::MenuItemFont:
    case QPlatformTheme::MessageBoxFont:
    case QPlatformTheme::LabelFont:
    case QPlatformTheme::StatusBarFont:
    case QPlatformTheme::TitleBarFont:
    case QPlatformTheme::MdiSubWindowTitleFont:
    case QPlatformTheme::DockWidgetTitleFont:
    case QPlatformTheme::PushButtonFont:
    case QPlatformTheme::CheckBoxFont:
    case QPlatformTheme::RadioButtonFont:
    case QPlatformTheme::ToolButtonFont:
    case QPlatformTheme::ItemViewFont:
    case QPlatformTheme::ListViewFont:
    case QPlatformTheme::HeaderViewFont:
    case QPlatformTheme::ListBoxFont:
    case QPlatformTheme::ComboLineEditFont:
    case QPlatformTheme::SmallFont:
    case QPlatformTheme::MiniFont:
    case QPlatformTheme::FixedFont:
    case QPlatformTheme::EditorFont:
    case QPlatformTheme::NFonts:
    default:
        return &m_suruUnits->fontParagraph();
    }
}
