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

#include "qquicksurustyle_p.h"

#include <QtCore/qdebug.h>
#include <QtCore/qsettings.h>
#include <QtQml/qqmlinfo.h>
#include <QtQuickControls2/private/qquickstyleattached_p.h>

QT_BEGIN_NAMESPACE

static QRgb qquicksuru_color(QQuickSuruStyle::Color colorRole)
{  
    static const QRgb colors[] = {
        0xFFFFFFFF, // White
        0xFFF5F5F5, // Porcelain
        0xFFCDCDCD, // Silk
        0xFF888888, // Ash

        0xFF111111, // Jet
        0xFF3B3B3B, // Inkstone
        0xFF5D5D5D, // Slate
        0xFF666666, // Graphite

        0xFF007AA6, // Blue
        0xFF3EB34F, // Green
        0xFFEF9928, // Yellow
        0xFFE95420, // Orange
        0xFFED3146, // Red
        0xFF762572  // Purple
    };
    return colors[colorRole];
}


// If no value was inherited from a parent or explicitly set, the "global" values are used.
// The initial, default values of the globals are hard-coded here, but the environment
// variables and .conf file override them if specified.
static QQuickSuruStyle::Theme globalTheme = QQuickSuruStyle::Light;

static uint globalAccent        = qquicksuru_color(QQuickSuruStyle::Blue);
static uint globalPositive      = qquicksuru_color(QQuickSuruStyle::Green);
static uint globalNegative      = qquicksuru_color(QQuickSuruStyle::Red);
static uint globalWarning       = qquicksuru_color(QQuickSuruStyle::Yellow);
static uint globalInformation   = qquicksuru_color(QQuickSuruStyle::Blue);

static uint globalLightHigh     = qquicksuru_color(QQuickSuruStyle::White);
static uint globalLightMidHigh  = qquicksuru_color(QQuickSuruStyle::Porcelain);
static uint globalLightMid      = qquicksuru_color(QQuickSuruStyle::Silk);
static uint globalLightMidLow   = qquicksuru_color(QQuickSuruStyle::Graphite);
static uint globalLightLow      = qquicksuru_color(QQuickSuruStyle::Jet);

static uint globalDarkHigh      = qquicksuru_color(QQuickSuruStyle::Porcelain);
static uint globalDarkMidHigh   = qquicksuru_color(QQuickSuruStyle::Silk);
static uint globalDarkMid       = qquicksuru_color(QQuickSuruStyle::Graphite);
static uint globalDarkMidLow    = qquicksuru_color(QQuickSuruStyle::Inkstone);
static uint globalDarkLow       = qquicksuru_color(QQuickSuruStyle::Jet);

// These represent whether a global foreground/background was set.
// Each style's m_hasForeground/m_hasBackground are initialized to these values.
static bool hasGlobalAccent = false;
static bool hasGlobalPositive = false;
static bool hasGlobalNegative = false;
static bool hasGlobalWarning = false;
static bool hasGlobalInformation = false;

static bool hasGlobalLightHigh = false;
static bool hasGlobalLightMidHigh = false;
static bool hasGlobalLightMid = false;
static bool hasGlobalLightMidLow = false;
static bool hasGlobalLightLow = false;

static bool hasGlobalDarkHigh = false;
static bool hasGlobalDarkMidHigh = false;
static bool hasGlobalDarkMid = false;
static bool hasGlobalDarkMidLow = false;
static bool hasGlobalDarkLow = false;

// These represent whether or not the global color value was specified as one of the
// values that QColor accepts, as opposed to one of the pre-defined colors like Red.
static bool globalAccentCustom = false;
static bool globalPositiveCustom = false;
static bool globalNegativeCustom = true;
static bool globalWarningCustom = true;
static bool globalInformationCustom = false;

static bool globalLightHighCustom = false;
static bool globalLightMidHighCustom = false;
static bool globalLightMidCustom = false;
static bool globalLightMidLowCustom = true;
static bool globalLightLowCustom = true;

static bool globalDarkHighCustom = false;
static bool globalDarkMidHighCustom = false;
static bool globalDarkMidCustom = false;
static bool globalDarkMidLowCustom = true;
static bool globalDarkLowCustom = true;

extern bool qt_is_dark_system_theme();

static QQuickSuruStyle::Theme qquicksuru_effective_theme(QQuickSuruStyle::Theme theme)
{
    if (theme == QQuickSuruStyle::System)
        theme = qt_is_dark_system_theme() ? QQuickSuruStyle::Dark : QQuickSuruStyle::Light;
    return theme;
}

QQuickSuruStyle::QQuickSuruStyle(QObject *parent) : QQuickStyleAttached(parent),
    m_explicitTheme(false),
    m_explicitAccent(false),
    m_explicitPositive(false),
    m_explicitNegative(false),
    m_explicitWarning(false),
    m_explicitInformation(false),

    m_explicitLightHigh(false),
    m_explicitLightMidHigh(false),
    m_explicitLightMid(false),
    m_explicitLightMidLow(false),
    m_explicitLightLow(false),

    m_explicitDarkHigh(false),
    m_explicitDarkMidHigh(false),
    m_explicitDarkMid(false),
    m_explicitDarkMidLow(false),
    m_explicitDarkLow(false),

    m_customAccent(globalAccentCustom),
    m_customPositive(globalPositiveCustom),
    m_customNegative(globalNegativeCustom),
    m_customWarning(globalWarningCustom),
    m_customInformation(globalInformationCustom),

    m_customLightHigh(globalLightHighCustom),
    m_customLightMidHigh(globalLightMidHighCustom),
    m_customLightMid(globalLightMidCustom),
    m_customLightMidLow(globalLightMidLowCustom),
    m_customLightLow(globalLightLowCustom),

    m_customDarkHigh(globalDarkHighCustom),
    m_customDarkMidHigh(globalDarkMidHighCustom),
    m_customDarkMid(globalDarkMidCustom),
    m_customDarkMidLow(globalDarkMidLowCustom),
    m_customDarkLow(globalDarkLowCustom),

    m_hasAccent(hasGlobalAccent),
    m_hasPositive(hasGlobalPositive),
    m_hasNegative(hasGlobalNegative),
    m_hasWarning(hasGlobalWarning),
    m_hasInformation(hasGlobalInformation),

    m_hasLightHigh(hasGlobalLightHigh),
    m_hasLightMidHigh(hasGlobalLightMidHigh),
    m_hasLightMid(hasGlobalLightMid),
    m_hasLightMidLow(hasGlobalLightMidLow),
    m_hasLightLow(hasGlobalLightLow),

    m_hasDarkHigh(hasGlobalDarkHigh),
    m_hasDarkMidHigh(hasGlobalDarkMidHigh),
    m_hasDarkMid(hasGlobalDarkMid),
    m_hasDarkMidLow(hasGlobalDarkMidLow),
    m_hasDarkLow(hasGlobalDarkLow),

    m_theme(globalTheme),
    m_accent(globalAccent),
    m_positive(globalPositive),
    m_negative(globalNegative),
    m_warning(globalWarning),
    m_information(globalInformation),

    m_lightHigh(globalLightHigh),
    m_lightMidHigh(globalLightMidHigh),
    m_lightMid(globalLightMid),
    m_lightMidLow(globalLightMidLow),
    m_lightLow(globalLightLow),

    m_darkHigh(globalDarkHigh),
    m_darkMidHigh(globalDarkMidHigh),
    m_darkMid(globalDarkMid),
    m_darkMidLow(globalDarkMidLow),
    m_darkLow(globalDarkLow)
{
    init();
}

QQuickSuruStyle *QQuickSuruStyle::qmlAttachedProperties(QObject *object)
{
    return new QQuickSuruStyle(object);
}

QQuickSuruStyle::Theme QQuickSuruStyle::theme() const
{
    return m_theme;
}

void QQuickSuruStyle::setTheme(Theme theme)
{
    if (theme == System)
        theme = qt_is_dark_system_theme() ? Dark : Light;

    m_explicitTheme = true;
    if (m_theme == theme)
        return;

    m_theme = theme;
    propagateTheme();

    emit themeChanged();
    emit paletteChanged();

    if (!m_customAccent)
        emit accentChanged();
    if (!m_customPositive)
        emit positiveChanged();
    if (!m_customNegative)
        emit negativeChanged();
    if (!m_customWarning)
        emit warningChanged();
    if (!m_customInformation)
        emit informationChanged();

    if (!m_customLightHigh)
        emit lightHighChanged();
    if (!m_customLightMidHigh)
        emit lightMidHighChanged();
    if (!m_customLightMid)
        emit lightMidChanged();
    if (!m_customLightMidLow)
        emit lightMidLowChanged();
    if (!m_customLightLow)
        emit lightLowChanged();

    if (!m_customDarkHigh)
        emit darkHighChanged();
    if (!m_customDarkMidHigh)
        emit darkMidHighChanged();
    if (!m_customDarkMid)
        emit darkMidChanged();
    if (!m_customDarkMidLow)
        emit darkMidLowChanged();
    if (!m_customDarkLow)
        emit darkLowChanged();
}

void QQuickSuruStyle::inheritTheme(Theme theme)
{
    if (m_explicitTheme || m_theme == theme)
        return;

    m_theme = theme;
    propagateTheme();

    emit themeChanged();
    emit paletteChanged();

    if (!m_customAccent)
        emit accentChanged();
    if (!m_customPositive)
        emit positiveChanged();
    if (!m_customNegative)
        emit negativeChanged();
    if (!m_customWarning)
        emit warningChanged();
    if (!m_customInformation)
        emit informationChanged();

    if (!m_customLightHigh)
        emit lightHighChanged();
    if (!m_customLightMidHigh)
        emit lightMidHighChanged();
    if (!m_customLightMid)
        emit lightMidChanged();
    if (!m_customLightMidLow)
        emit lightMidLowChanged();
    if (!m_customLightLow)
        emit lightLowChanged();

    if (!m_customDarkHigh)
        emit darkHighChanged();
    if (!m_customDarkMidHigh)
        emit darkMidHighChanged();
    if (!m_customDarkMid)
        emit darkMidChanged();
    if (!m_customDarkMidLow)
        emit darkMidLowChanged();
    if (!m_customDarkLow)
        emit darkLowChanged();
}

void QQuickSuruStyle::propagateTheme()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritTheme(m_theme);
    }
}

void QQuickSuruStyle::resetTheme()
{
    if (!m_explicitTheme)
        return;

    m_explicitTheme = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    inheritTheme(suru ? suru->theme() : globalTheme);
}

// Accent color
QVariant QQuickSuruStyle::accent() const
{
    return accentColor();
}

void QQuickSuruStyle::setAccent(const QVariant &var)
{
    QRgb accent = 0;
    bool custom = false;
    if (!variantToRgba(var, "accent", &accent, &custom))
        return;

    m_explicitAccent = true;
    if (m_accent == accent)
        return;

    m_customAccent = custom;
    m_accent = accent;
    propagateAccent();
    emit accentChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritAccent(QRgb accent, bool custom)
{
    if (m_explicitAccent || m_accent == accent)
        return;

    m_customAccent = custom;
    m_accent = accent;
    propagateAccent();
    emit accentChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateAccent()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritAccent(m_accent, m_customAccent);
    }
}

void QQuickSuruStyle::resetAccent()
{
    if (!m_explicitAccent)
        return;

    m_customAccent = false;
    m_explicitAccent = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritAccent(suru->m_accent, suru->m_customAccent);
    else
        inheritAccent(globalAccent, false);
}

// Positive color
QVariant QQuickSuruStyle::positive() const
{
    return positiveColor();
}

void QQuickSuruStyle::setPositive(const QVariant &var)
{
    QRgb positive = 0;
    bool custom = false;
    if (!variantToRgba(var, "positive", &positive, &custom))
        return;

    m_explicitPositive = true;
    if (m_positive == positive)
        return;

    m_customPositive = custom;
    m_positive = positive;
    propagatePositive();
    emit positiveChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritPositive(QRgb positive, bool custom)
{
    if (m_explicitPositive || m_positive == positive)
        return;

    m_customPositive = custom;
    m_positive = positive;
    propagatePositive();
    emit positiveChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagatePositive()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritPositive(m_positive, m_customPositive);
    }
}

void QQuickSuruStyle::resetPositive()
{
    if (!m_explicitPositive)
        return;

    m_customPositive = false;
    m_explicitPositive = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritPositive(suru->m_positive, suru->m_customPositive);
    else
        inheritPositive(globalPositive, false);
}


// Negative color
QVariant QQuickSuruStyle::negative() const
{
    return negativeColor();
}

void QQuickSuruStyle::setNegative(const QVariant &var)
{
    QRgb negative = 0;
    bool custom = false;
    if (!variantToRgba(var, "negative", &negative, &custom))
        return;

    m_explicitNegative = true;
    if (m_negative == negative)
        return;

    m_customNegative = custom;
    m_negative = negative;
    propagateNegative();
    emit negativeChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritNegative(QRgb negative, bool custom)
{
    if (m_explicitNegative || m_negative == negative)
        return;

    m_customNegative = custom;
    m_negative = negative;
    propagateNegative();
    emit negativeChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateNegative()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritNegative(m_negative, m_customNegative);
    }
}

void QQuickSuruStyle::resetNegative()
{
    if (!m_explicitNegative)
        return;

    m_customNegative = false;
    m_explicitNegative = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritNegative(suru->m_negative, suru->m_customNegative);
    else
        inheritNegative(globalNegative, false);
}


// Warning color
QVariant QQuickSuruStyle::warning() const
{
    return warningColor();
}

void QQuickSuruStyle::setWarning(const QVariant &var)
{
    QRgb warning = 0;
    bool custom = false;
    if (!variantToRgba(var, "warning", &warning, &custom))
        return;

    m_explicitWarning = true;
    if (m_warning == warning)
        return;

    m_customWarning = custom;
    m_warning = warning;
    propagateWarning();
    emit warningChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritWarning(QRgb warning, bool custom)
{
    if (m_explicitWarning || m_warning == warning)
        return;

    m_customWarning = custom;
    m_warning = warning;
    propagateWarning();
    emit warningChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateWarning()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritWarning(m_warning, m_customWarning);
    }
}

void QQuickSuruStyle::resetWarning()
{
    if (!m_explicitWarning)
        return;

    m_customWarning = false;
    m_explicitWarning = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritWarning(suru->m_warning, suru->m_customWarning);
    else
        inheritWarning(globalWarning, false);
}


// Information color
QVariant QQuickSuruStyle::information() const
{
    return informationColor();
}

void QQuickSuruStyle::setInformation(const QVariant &var)
{
    QRgb information = 0;
    bool custom = false;
    if (!variantToRgba(var, "information", &information, &custom))
        return;

    m_explicitInformation = true;
    if (m_information == information)
        return;

    m_customInformation = custom;
    m_information = information;
    propagateInformation();
    emit informationChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritInformation(QRgb information, bool custom)
{
    if (m_explicitInformation || m_information == information)
        return;

    m_customInformation = custom;
    m_information = information;
    propagateInformation();
    emit informationChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateInformation()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritInformation(m_information, m_customInformation);
    }
}

void QQuickSuruStyle::resetInformation()
{
    if (!m_explicitInformation)
        return;

    m_customInformation = false;
    m_explicitInformation = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritInformation(suru->m_information, suru->m_customInformation);
    else
        inheritInformation(globalInformation, false);
}


// Light theme - High color
QVariant QQuickSuruStyle::lightHigh() const
{
    return QColor::fromRgba(m_lightHigh);
}

void QQuickSuruStyle::setLightHigh(const QVariant &var)
{
    QRgb lightHigh = 0;
    bool custom = false;
    if (!variantToRgba(var, "lightHigh", &lightHigh, &custom))
        return;

    m_explicitLightHigh = true;
    if (m_lightHigh == lightHigh)
        return;

    m_customLightHigh = custom;
    m_lightHigh = lightHigh;
    propagateLightHigh();
    emit lightHighChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritLightHigh(QRgb lightHigh, bool custom)
{
    if (m_explicitLightHigh || m_lightHigh == lightHigh)
        return;

    m_customLightHigh = custom;
    m_lightHigh = lightHigh;
    propagateLightHigh();
    emit lightHighChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateLightHigh()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritLightHigh(m_lightHigh, m_customLightHigh);
    }
}

void QQuickSuruStyle::resetLightHigh()
{
    if (!m_explicitLightHigh)
        return;

    m_customLightHigh = false;
    m_explicitLightHigh = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritLightHigh(suru->m_lightHigh, suru->m_customLightHigh);
    else
        inheritLightHigh(globalLightHigh, false);
}


// Light theme - MidHigh color
QVariant QQuickSuruStyle::lightMidHigh() const
{
    return QColor::fromRgba(m_lightMidHigh);
}

void QQuickSuruStyle::setLightMidHigh(const QVariant &var)
{
    QRgb lightMidHigh = 0;
    bool custom = false;
    if (!variantToRgba(var, "lightMidHigh", &lightMidHigh, &custom))
        return;

    m_explicitLightMidHigh = true;
    if (m_lightMidHigh == lightMidHigh)
        return;

    m_customLightMidHigh = custom;
    m_lightMidHigh = lightMidHigh;
    propagateLightMidHigh();
    emit lightMidHighChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritLightMidHigh(QRgb lightMidHigh, bool custom)
{
    if (m_explicitLightMidHigh || m_lightMidHigh == lightMidHigh)
        return;

    m_customLightMidHigh = custom;
    m_lightMidHigh = lightMidHigh;
    propagateLightMidHigh();
    emit lightMidHighChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateLightMidHigh()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritLightMidHigh(m_lightMidHigh, m_customLightMidHigh);
    }
}

void QQuickSuruStyle::resetLightMidHigh()
{
    if (!m_explicitLightMidHigh)
        return;

    m_customLightMidHigh = false;
    m_explicitLightMidHigh = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritLightMidHigh(suru->m_lightMidHigh, suru->m_customLightMidHigh);
    else
        inheritLightMidHigh(globalLightMidHigh, false);
}


// Light theme - Mid color
QVariant QQuickSuruStyle::lightMid() const
{
    return QColor::fromRgba(m_lightMid);
}

void QQuickSuruStyle::setLightMid(const QVariant &var)
{
    QRgb lightMid = 0;
    bool custom = false;
    if (!variantToRgba(var, "lightMid", &lightMid, &custom))
        return;

    m_explicitLightMid = true;
    if (m_lightMid == lightMid)
        return;

    m_customLightMid = custom;
    m_lightMid = lightMid;
    propagateLightMid();
    emit lightMidChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritLightMid(QRgb lightMid, bool custom)
{
    if (m_explicitLightMid || m_lightMid == lightMid)
        return;

    m_customLightMid = custom;
    m_lightMid = lightMid;
    propagateLightMid();
    emit lightMidChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateLightMid()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritLightMid(m_lightMid, m_customLightMid);
    }
}

void QQuickSuruStyle::resetLightMid()
{
    if (!m_explicitLightMid)
        return;

    m_customLightMid = false;
    m_explicitLightMid = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritLightMid(suru->m_lightMid, suru->m_customLightMid);
    else
        inheritLightMid(globalLightMid, false);
}


// Light theme - MidLow color
QVariant QQuickSuruStyle::lightMidLow() const
{
    return QColor::fromRgba(m_lightMidLow);
}

void QQuickSuruStyle::setLightMidLow(const QVariant &var)
{
    QRgb lightMidLow = 0;
    bool custom = false;
    if (!variantToRgba(var, "lightMidLow", &lightMidLow, &custom))
        return;

    m_explicitLightMidLow = true;
    if (m_lightMidLow == lightMidLow)
        return;

    m_customLightMidLow = custom;
    m_lightMidLow = lightMidLow;
    propagateLightMidLow();
    emit lightMidLowChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritLightMidLow(QRgb lightMidLow, bool custom)
{
    if (m_explicitLightMidLow || m_lightMidLow == lightMidLow)
        return;

    m_customLightMidLow = custom;
    m_lightMidLow = lightMidLow;
    propagateLightMidLow();
    emit lightMidLowChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateLightMidLow()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritLightMidLow(m_lightMidLow, m_customLightMidLow);
    }
}

void QQuickSuruStyle::resetLightMidLow()
{
    if (!m_explicitLightMidLow)
        return;

    m_customLightMidLow = false;
    m_explicitLightMidLow = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritLightMidLow(suru->m_lightMidLow, suru->m_customLightMidLow);
    else
        inheritLightMidLow(globalLightMidLow, false);
}


// Light theme - Low color
QVariant QQuickSuruStyle::lightLow() const
{
    return QColor::fromRgba(m_lightLow);
}

void QQuickSuruStyle::setLightLow(const QVariant &var)
{
    QRgb lightLow = 0;
    bool custom = false;
    if (!variantToRgba(var, "lightLow", &lightLow, &custom))
        return;

    m_explicitLightLow = true;
    if (m_lightLow == lightLow)
        return;

    m_customLightLow = custom;
    m_lightLow = lightLow;
    propagateLightLow();
    emit lightLowChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritLightLow(QRgb lightLow, bool custom)
{
    if (m_explicitLightLow || m_lightLow == lightLow)
        return;

    m_customLightLow = custom;
    m_lightLow = lightLow;
    propagateLightLow();
    emit lightLowChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateLightLow()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritLightLow(m_lightLow, m_customLightLow);
    }
}

void QQuickSuruStyle::resetLightLow()
{
    if (!m_explicitLightLow)
        return;

    m_customLightLow = false;
    m_explicitLightLow = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritLightLow(suru->m_lightLow, suru->m_customLightLow);
    else
        inheritLightLow(globalLightLow, false);
}


// Dark theme - High color
QVariant QQuickSuruStyle::darkHigh() const
{
    return QColor::fromRgba(m_darkHigh);
}

void QQuickSuruStyle::setDarkHigh(const QVariant &var)
{
    QRgb darkHigh = 0;
    bool custom = false;
    if (!variantToRgba(var, "darkHigh", &darkHigh, &custom))
        return;

    m_explicitDarkHigh = true;
    if (m_darkHigh == darkHigh)
        return;

    m_customDarkHigh = custom;
    m_darkHigh = darkHigh;
    propagateDarkHigh();
    emit darkHighChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritDarkHigh(QRgb darkHigh, bool custom)
{
    if (m_explicitDarkHigh || m_darkHigh == darkHigh)
        return;

    m_customDarkHigh = custom;
    m_darkHigh = darkHigh;
    propagateDarkHigh();
    emit darkHighChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateDarkHigh()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritDarkHigh(m_darkHigh, m_customDarkHigh);
    }
}

void QQuickSuruStyle::resetDarkHigh()
{
    if (!m_explicitDarkHigh)
        return;

    m_customDarkHigh = false;
    m_explicitDarkHigh = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritDarkHigh(suru->m_darkHigh, suru->m_customDarkHigh);
    else
        inheritDarkHigh(globalDarkHigh, false);
}


// Dark theme - MidHigh color
QVariant QQuickSuruStyle::darkMidHigh() const
{
    return QColor::fromRgba(m_darkMidHigh);
}

void QQuickSuruStyle::setDarkMidHigh(const QVariant &var)
{
    QRgb darkMidHigh = 0;
    bool custom = false;
    if (!variantToRgba(var, "darkMidHigh", &darkMidHigh, &custom))
        return;

    m_explicitDarkMidHigh = true;
    if (m_darkMidHigh == darkMidHigh)
        return;

    m_customDarkMidHigh = custom;
    m_darkMidHigh = darkMidHigh;
    propagateDarkMidHigh();
    emit darkMidHighChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritDarkMidHigh(QRgb darkMidHigh, bool custom)
{
    if (m_explicitDarkMidHigh || m_darkMidHigh == darkMidHigh)
        return;

    m_customDarkMidHigh = custom;
    m_darkMidHigh = darkMidHigh;
    propagateDarkMidHigh();
    emit darkMidHighChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateDarkMidHigh()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritDarkMidHigh(m_darkMidHigh, m_customDarkMidHigh);
    }
}

void QQuickSuruStyle::resetDarkMidHigh()
{
    if (!m_explicitDarkMidHigh)
        return;

    m_customDarkMidHigh = false;
    m_explicitDarkMidHigh = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritDarkMidHigh(suru->m_darkMidHigh, suru->m_customDarkMidHigh);
    else
        inheritDarkMidHigh(globalDarkMidHigh, false);
}


// Dark theme - Mid color
QVariant QQuickSuruStyle::darkMid() const
{
    return QColor::fromRgba(m_darkMid);
}

void QQuickSuruStyle::setDarkMid(const QVariant &var)
{
    QRgb darkMid = 0;
    bool custom = false;
    if (!variantToRgba(var, "darkMid", &darkMid, &custom))
        return;

    m_explicitDarkMid = true;
    if (m_darkMid == darkMid)
        return;

    m_customDarkMid = custom;
    m_darkMid = darkMid;
    propagateDarkMid();
    emit darkMidChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritDarkMid(QRgb darkMid, bool custom)
{
    if (m_explicitDarkMid || m_darkMid == darkMid)
        return;

    m_customDarkMid = custom;
    m_darkMid = darkMid;
    propagateDarkMid();
    emit darkMidChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateDarkMid()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritDarkMid(m_darkMid, m_customDarkMid);
    }
}

void QQuickSuruStyle::resetDarkMid()
{
    if (!m_explicitDarkMid)
        return;

    m_customDarkMid = false;
    m_explicitDarkMid = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritDarkMid(suru->m_darkMid, suru->m_customDarkMid);
    else
        inheritDarkMid(globalDarkMid, false);
}


// Dark theme - MidLow color
QVariant QQuickSuruStyle::darkMidLow() const
{
    return QColor::fromRgba(m_darkMidLow);
}

void QQuickSuruStyle::setDarkMidLow(const QVariant &var)
{
    QRgb darkMidLow = 0;
    bool custom = false;
    if (!variantToRgba(var, "darkMidLow", &darkMidLow, &custom))
        return;

    m_explicitDarkMidLow = true;
    if (m_darkMidLow == darkMidLow)
        return;

    m_customDarkMidLow = custom;
    m_darkMidLow = darkMidLow;
    propagateDarkMidLow();
    emit darkMidLowChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritDarkMidLow(QRgb darkMidLow, bool custom)
{
    if (m_explicitDarkMidLow || m_darkMidLow == darkMidLow)
        return;

    m_customDarkMidLow = custom;
    m_darkMidLow = darkMidLow;
    propagateDarkMidLow();
    emit darkMidLowChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateDarkMidLow()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritDarkMidLow(m_darkMidLow, m_customDarkMidLow);
    }
}

void QQuickSuruStyle::resetDarkMidLow()
{
    if (!m_explicitDarkMidLow)
        return;

    m_customDarkMidLow = false;
    m_explicitDarkMidLow = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritDarkMidLow(suru->m_darkMidLow, suru->m_customDarkMidLow);
    else
        inheritDarkMidLow(globalDarkMidLow, false);
}


// Dark theme - Low color
QVariant QQuickSuruStyle::darkLow() const
{
    return QColor::fromRgba(m_darkLow);
}

void QQuickSuruStyle::setDarkLow(const QVariant &var)
{
    QRgb darkLow = 0;
    bool custom = false;
    if (!variantToRgba(var, "darkLow", &darkLow, &custom))
        return;

    m_explicitDarkLow = true;
    if (m_darkLow == darkLow)
        return;

    m_customDarkLow = custom;
    m_darkLow = darkLow;
    propagateDarkLow();
    emit darkLowChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritDarkLow(QRgb darkLow, bool custom)
{
    if (m_explicitDarkLow || m_darkLow == darkLow)
        return;

    m_customDarkLow = custom;
    m_darkLow = darkLow;
    propagateDarkLow();
    emit darkLowChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateDarkLow()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritDarkLow(m_darkLow, m_customDarkLow);
    }
}

void QQuickSuruStyle::resetDarkLow()
{
    if (!m_explicitDarkLow)
        return;

    m_customDarkLow = false;
    m_explicitDarkLow = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritDarkLow(suru->m_darkLow, suru->m_customDarkLow);
    else
        inheritDarkLow(globalDarkLow, false);
}

QColor QQuickSuruStyle::color(Color color) const
{
    return qquicksuru_color(color);
}

QColor QQuickSuruStyle::accentColor() const
{
    return QColor::fromRgba(m_accent);
}

QColor QQuickSuruStyle::positiveColor() const
{
    return QColor::fromRgba(m_positive);
}

QColor QQuickSuruStyle::negativeColor() const
{
    return QColor::fromRgba(m_negative);
}

QColor QQuickSuruStyle::warningColor() const
{
    return QColor::fromRgba(m_warning);
}

QColor QQuickSuruStyle::informationColor() const
{
    return QColor::fromRgba(m_information);
}

QColor QQuickSuruStyle::backgroundColor() const
{
    return QColor::fromRgba(m_theme == Light ? m_lightHigh : m_darkLow);
}

QColor QQuickSuruStyle::secondaryBackgroundColor() const
{
    return QColor::fromRgba(m_theme == Light ? m_lightMidHigh : m_darkMidLow);
}

QColor QQuickSuruStyle::neutralColor() const
{
    return QColor::fromRgba(m_theme == Light ? m_lightMid : m_darkMid);
}

QColor QQuickSuruStyle::secondaryForegroundColor() const
{
    return QColor::fromRgba(m_theme == Light ? m_lightMidLow : m_darkMidHigh);
}

QColor QQuickSuruStyle::foregroundColor() const
{
    return QColor::fromRgba(m_theme == Light ? m_lightLow : m_darkHigh);
}

void QQuickSuruStyle::parentStyleChange(QQuickStyleAttached *newParent, QQuickStyleAttached *oldParent)
{
    Q_UNUSED(oldParent);
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(newParent);
    if (suru) {
        inheritTheme(suru->theme());

        inheritAccent(suru->m_accent, suru->m_customAccent);
        inheritPositive(suru->m_positive, suru->m_customPositive);
        inheritNegative(suru->m_negative, suru->m_customNegative);
        inheritWarning(suru->m_warning, suru->m_customWarning);
        inheritInformation(suru->m_information, suru->m_customInformation);

        inheritLightHigh(suru->m_lightHigh, suru->m_customLightHigh);
        inheritLightMidHigh(suru->m_lightMidHigh, suru->m_customLightMidHigh);
        inheritLightMid(suru->m_lightMid, suru->m_customLightMid);
        inheritLightMidLow(suru->m_lightMidLow, suru->m_customLightMidLow);
        inheritLightLow(suru->m_lightLow, suru->m_customLightLow);

        inheritDarkHigh(suru->m_darkHigh, suru->m_customDarkHigh);
        inheritDarkMidHigh(suru->m_darkMidHigh, suru->m_customDarkMidHigh);
        inheritDarkMid(suru->m_darkMid, suru->m_customDarkMid);
        inheritDarkMidLow(suru->m_darkMidLow, suru->m_customDarkMidLow);
        inheritDarkLow(suru->m_darkLow, suru->m_customDarkLow);
    }
}

template <typename Enum>
static Enum toEnumValue(const QByteArray &value, bool *ok)
{
    QMetaEnum enumeration = QMetaEnum::fromType<Enum>();
    return static_cast<Enum>(enumeration.keyToValue(value, ok));
}

static QByteArray resolveSetting(const QByteArray &env, const QSharedPointer<QSettings> &settings, const QString &name)
{
    QByteArray value = qgetenv(env);
    if (value.isNull() && !settings.isNull())
        value = settings->value(name).toByteArray();
    return value;
}

void QQuickSuruStyle::init()
{
    static bool globalsInitialized = false;
    if (!globalsInitialized) {
        QSharedPointer<QSettings> settings = QQuickStyleAttached::settings(QStringLiteral("Suru"));

        bool ok = false;
        QByteArray themeValue = resolveSetting("QT_QUICK_CONTROLS_SURU_THEME", settings, QStringLiteral("Theme"));
        Theme themeEnum = toEnumValue<Theme>(themeValue, &ok);
        if (ok)
            globalTheme = m_theme = qquicksuru_effective_theme(themeEnum);
        else if (!themeValue.isEmpty())
            qWarning().nospace().noquote() << "Suru: unknown theme value: " << themeValue;


        solveSuruColor(globalAccentCustom, m_customAccent, globalAccent, m_accent,
                       "QT_QUICK_CONTROLS_SURU_ACCENT", settings, QStringLiteral("Accent"));

        solveSuruColor(globalPositiveCustom, m_customPositive, globalPositive, m_positive,
                       "QT_QUICK_CONTROLS_SURU_POSITIVE", settings, QStringLiteral("Positive"));

        solveSuruColor(globalNegativeCustom, m_customNegative, globalNegative, m_negative,
                       "QT_QUICK_CONTROLS_SURU_NEGATIVE", settings, QStringLiteral("Negative"));

        solveSuruColor(globalWarningCustom, m_customWarning, globalWarning, m_warning,
                       "QT_QUICK_CONTROLS_SURU_WARNING", settings, QStringLiteral("Warning"));

        solveSuruColor(globalInformationCustom, m_customInformation, globalInformation, m_information,
                       "QT_QUICK_CONTROLS_SURU_INFORMATION", settings, QStringLiteral("Information"));


        solveSuruColor(globalLightHighCustom, m_customLightHigh, globalLightHigh, m_lightHigh,
                       "QT_QUICK_CONTROLS_SURU_LIGHT_HIGH", settings, QStringLiteral("LightHigh"));

        solveSuruColor(globalLightMidHighCustom, m_customLightMidHigh, globalLightMidHigh, m_lightMidHigh,
                       "QT_QUICK_CONTROLS_SURU_LIGHT_MIDHIGH", settings, QStringLiteral("LightMidHigh"));

        solveSuruColor(globalLightMidCustom, m_customLightMid, globalLightMid, m_lightMid,
                       "QT_QUICK_CONTROLS_SURU_LIGHT_MID", settings, QStringLiteral("LightMid"));

        solveSuruColor(globalLightMidLowCustom, m_customLightMidLow, globalLightMidLow, m_lightMidLow,
                       "QT_QUICK_CONTROLS_SURU_LIGHT_MIDLOW", settings, QStringLiteral("LightMidLow"));

        solveSuruColor(globalLightLowCustom, m_customLightLow, globalLightLow, m_lightLow,
                       "QT_QUICK_CONTROLS_SURU_LIGHT_LOW", settings, QStringLiteral("LightLow"));


        solveSuruColor(globalDarkHighCustom, m_customDarkHigh, globalDarkHigh, m_darkHigh,
                       "QT_QUICK_CONTROLS_SURU_DARK_HIGH", settings, QStringLiteral("DarkHigh"));

        solveSuruColor(globalDarkMidHighCustom, m_customDarkMidHigh, globalDarkMidHigh, m_darkMidHigh,
                       "QT_QUICK_CONTROLS_SURU_DARK_MIDHIGH", settings, QStringLiteral("DarkMidHigh"));

        solveSuruColor(globalDarkMidCustom, m_customDarkMid, globalDarkMid, m_darkMid,
                       "QT_QUICK_CONTROLS_SURU_DARK_MID", settings, QStringLiteral("DarkMid"));

        solveSuruColor(globalDarkMidLowCustom, m_customDarkMidLow, globalDarkMidLow, m_darkMidLow,
                       "QT_QUICK_CONTROLS_SURU_DARK_MIDLOW", settings, QStringLiteral("DarkMidLow"));

        solveSuruColor(globalDarkLowCustom, m_customDarkLow, globalDarkLow, m_darkLow,
                       "QT_QUICK_CONTROLS_SURU_DARK_LOW", settings, QStringLiteral("DarkLow"));


        globalsInitialized = true;
    }

    QQuickStyleAttached::init(); // TODO: lazy init?
}

void QQuickSuruStyle::solveSuruColor(bool &globalCustom, bool &localCustom,
                                     QRgb &globalColor, QRgb &localColor,
                                     const QByteArray &env, QSharedPointer<QSettings> settings, const QString &name) const

{
    QByteArray value = resolveSetting(env, settings, name);

    bool ok = false;
    Color colorEnum = toEnumValue<Color>(value, &ok);

    if (ok) {
        globalCustom = localCustom = false;
        globalColor = localColor = qquicksuru_color(colorEnum);
    } else if (!value.isEmpty()) {
        QColor color(value.constData());
        if (color.isValid()) {
            globalCustom = localCustom = true;
            globalColor = localColor = color.rgba();
        } else {
            qWarning().nospace().noquote() << "Suru: unknown " << name << " value: " << value;
        }
    }
}

bool QQuickSuruStyle::variantToRgba(const QVariant &var, const char *name, QRgb *rgba, bool *custom) const
{
    *custom = false;
    if (var.type() == QVariant::Int) {
        int val = var.toInt();
        if (val < White || val > Purple) {
            qmlInfo(parent()) << "unknown Suru." << name << " value: " << val;
            return false;
        }
        *rgba = qquicksuru_color(static_cast<Color>(val));
    } else {
        int val = QMetaEnum::fromType<Color>().keyToValue(var.toByteArray());
        if (val != -1) {
            *rgba = qquicksuru_color(static_cast<Color>(val));
        } else {
            QColor color(var.toString());
            if (!color.isValid()) {
                qmlInfo(parent()) << "unknown Suru." << name << " value: " << var.toString();
                return false;
            }
            *custom = true;
            *rgba = color.rgba();
        }
    }
    return true;
}

QT_END_NAMESPACE
