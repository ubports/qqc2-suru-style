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
#include "qquicksuruanimations.h"
#include "qquicksuruunits.h"

#include <QtCore/qdebug.h>
#include <QtCore/qsettings.h>
#include <QtCore/qstandardpaths.h>
#include <QtQml/qqmlinfo.h>
#include <QtQuickControls2/private/qquickstyle_p.h>

static QRgb qquicksuru_color(QQuickSuruStyle::Color colorRole)
{
    static const QRgb colors[] = {
        0xFF000000, // Black
        0xFF111111, // Jet
        0xff333333, // Inkstone
        0xFF666666, // Graphite
        0xFF888888, // Ash
        0xFFcdcdcd, // Silk
        0xFFf7f7f7, // Porcelain
        0xFFffffff, // White

        0xFF335280, // Blue
        0xFF0e8420, // Green
        0xFFc7162b, // Red
        0xFFf99b0f, // Yellow
        0xFFe95420, // Orange
        0xFF762572, // Purple
        0xFF19b6ee, // LightBlue
        0xFF3eb34f, // LightGreen
        0xFFef9928, // LightYellow
        0xFFed3146, // LightRed
    };

    return colors[colorRole];
}

static QQuickSuruStyle::Theme globalTheme = QQuickSuruStyle::Light;

static uint globalColors[2][9] = {
    // Light theme
    {
        qquicksuru_color(QQuickSuruStyle::Green),       // lightPositive
        qquicksuru_color(QQuickSuruStyle::Red),         // lightNegative
        qquicksuru_color(QQuickSuruStyle::Yellow),      // lightWarning
        qquicksuru_color(QQuickSuruStyle::Blue),        // lightInformation
        qquicksuru_color(QQuickSuruStyle::White),       // lightHigh
        qquicksuru_color(QQuickSuruStyle::Porcelain),   // lightMidHigh
        qquicksuru_color(QQuickSuruStyle::Silk),        // lightMid
        qquicksuru_color(QQuickSuruStyle::Graphite),    // lightMidLow
        qquicksuru_color(QQuickSuruStyle::Jet)          // lightLow
    },

    // Dark theme
    {
        qquicksuru_color(QQuickSuruStyle::LightGreen),  // darkPositive
        qquicksuru_color(QQuickSuruStyle::LightRed),    // darkNegative
        qquicksuru_color(QQuickSuruStyle::LightYellow), // darkWarning
        qquicksuru_color(QQuickSuruStyle::LightBlue),   // darkInformation
        qquicksuru_color(QQuickSuruStyle::Porcelain),   // darkHigh
        qquicksuru_color(QQuickSuruStyle::Silk),        // darkMidHigh
        qquicksuru_color(QQuickSuruStyle::Graphite),    // darkMid
        qquicksuru_color(QQuickSuruStyle::Inkstone),    // darkMidLow
        qquicksuru_color(QQuickSuruStyle::Jet)          // darkLow
    }
};

static bool globalCustoms[2][9] = { { false } };

static const QString settingsFile = QStringLiteral("%1/ubuntu-ui-toolkit/theme.ini");
static const QString ubuntuDarkTheme = QStringLiteral("Ubuntu.Components.Themes.SuruDark");

static bool qt_is_dark_system_theme() {
    bool is_dark = false;

    // TODO make this work on OSs other than Ubuntu Touch
    QSettings settings(settingsFile.arg(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)), QSettings::IniFormat);
    QString themeName = settings.value(QStringLiteral("theme")).toString();
    if (themeName == ubuntuDarkTheme) {
        is_dark = true;
    }

    return is_dark;
};

static QQuickSuruStyle::Theme qquicksuru_effective_theme(QQuickSuruStyle::Theme theme)
{
    if (theme == QQuickSuruStyle::System)
        theme = qt_is_dark_system_theme() ? QQuickSuruStyle::Dark : QQuickSuruStyle::Light;
    return theme;
}

QQuickSuruStyle::QQuickSuruStyle(QObject *parent) : QQuickAttachedObject(parent),
    m_explicitTheme(false),
    m_theme(globalTheme),
    m_highlightType(InformationHighlight),
    m_textLevel(Paragraph),
    m_textStyle(PrimaryText)
{
    m_animations = new QQuickSuruAnimations(this);
    m_units = new QQuickSuruUnits(this);

    connect(this, &QQuickSuruStyle::highlightTypeChanged, this, &QQuickSuruStyle::paletteChanged);
    connect(this, &QQuickSuruStyle::textStyleChanged, this, &QQuickSuruStyle::paletteChanged);

    for (int i=0; i<2; ++i) {
        for (int j=0; j<9; ++j) {
            m_explicits[i][j] = false;
            m_customs[i][j] = globalCustoms[i][j];
            m_colors[i][j] = globalColors[i][j];
        }
    }

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

}

void QQuickSuruStyle::inheritTheme(Theme theme)
{
    if (m_explicitTheme || m_theme == theme)
        return;

    m_theme = theme;
    propagateTheme();

    emit themeChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateTheme()
{
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
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
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(attachedParent());
    inheritTheme(suru ? suru->theme() : globalTheme);
}

QQuickSuruStyle::HighlightType QQuickSuruStyle::highlightType() const
{
    return m_highlightType;
}

void QQuickSuruStyle::setHighlightType(QQuickSuruStyle::HighlightType type)
{
    if (m_highlightType == type)
        return;

    m_highlightType = type;
    emit highlightTypeChanged();
}

void QQuickSuruStyle::resetHighlightType()
{
    m_highlightType = InformationHighlight;
    emit highlightTypeChanged();
}

QQuickSuruStyle::TextLevel QQuickSuruStyle::textLevel() const
{
    return m_textLevel;
}

void QQuickSuruStyle::setTextLevel(QQuickSuruStyle::TextLevel level)
{
    if (m_textLevel == level)
        return;

    m_textLevel = level;
    emit textLevelChanged();
}

void QQuickSuruStyle::resetTextLevel()
{
    m_textLevel = Paragraph;
    emit textLevelChanged();
}

QQuickSuruStyle::TextStyle QQuickSuruStyle::textStyle() const
{
    return m_textStyle;
}

void QQuickSuruStyle::setTextStyle(QQuickSuruStyle::TextStyle style)
{
    if (m_textStyle == style)
        return;

    m_textStyle = style;
    emit textStyleChanged();
}

void QQuickSuruStyle::resetTextStyle()
{
    m_textStyle = PrimaryText;
    emit textStyleChanged();
}

void QQuickSuruStyle::inheritPaletteColor(const QQuickSuruStyle::Theme &theme, const QQuickSuruStyle::PaletteColor &paletteColor, QRgb value, bool custom)
{
    if (m_explicits[theme][paletteColor] || m_colors[theme][paletteColor] == value)
        return;

    m_customs[theme][paletteColor] = custom;
    m_colors[theme][paletteColor] = value;

    propagatePaletteColor(theme, paletteColor);

    emit paletteChanged();
}

void QQuickSuruStyle::propagatePaletteColor(const QQuickSuruStyle::Theme &theme, const QQuickSuruStyle::PaletteColor &paletteColor)
{
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);

        if (suru)
            suru->inheritPaletteColor(theme, paletteColor, m_colors[theme][paletteColor], m_customs[theme][paletteColor]);
    }
}

void QQuickSuruStyle::resetPaletteColor(const QQuickSuruStyle::Theme &theme, const QQuickSuruStyle::PaletteColor &paletteColor)
{
    if (!m_explicits[theme][paletteColor])
        return;

    m_customs[theme][paletteColor] = false;
    m_explicits[theme][paletteColor] = false;

    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(attachedParent());
    if (suru)
        inheritPaletteColor(theme, paletteColor, suru->m_colors[theme][paletteColor], suru->m_customs[theme][paletteColor]);
    else
        inheritPaletteColor(theme, paletteColor, globalColors[theme][paletteColor], false);
}

QColor QQuickSuruStyle::highlightColor() const
{
    return QColor::fromRgba(m_colors[m_theme][PaletteColor(m_highlightType)]);
}

QColor QQuickSuruStyle::activeFocusColor() const
{
    return QColor::fromRgba(m_colors[m_theme][InformationHighlight]);
}

QColor QQuickSuruStyle::overlayColor() const
{
    return color(Black, m_theme == Light ? 0.85 : 0.62);
}

QColor QQuickSuruStyle::backgroundColor() const
{
    return QColor::fromRgba(m_colors[m_theme][m_theme == Light ? High : Low]);
}

QColor QQuickSuruStyle::color(QQuickSuruStyle::Color color, qreal opacity) const
{
    QColor c = qquicksuru_color(color);
    c.setAlphaF(opacity);

    return c;
}

QColor QQuickSuruStyle::secondaryBackgroundColor() const
{
    return QColor::fromRgba(m_colors[m_theme][m_theme == Light ? MidHigh : MidLow]);
}

QColor QQuickSuruStyle::neutralColor() const
{
    return QColor::fromRgba(m_colors[m_theme][Mid]);
}

QColor QQuickSuruStyle::foregroundColor() const
{
    QColor c = QColor::fromRgba(m_colors[m_theme][m_theme == Light ? Low : High]);

    if (m_textStyle == SecondaryText)
        c.setAlphaF(0.8571);
    else if (m_textStyle == TertiaryText)
        c.setAlphaF(0.6429);

    return c;
}

void QQuickSuruStyle::attachedParentChange(QQuickAttachedObject *newParent, QQuickAttachedObject *oldParent)
{
    Q_UNUSED(oldParent);
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(newParent);
    if (suru) {
        Theme newTheme = suru->theme();
        inheritTheme(newTheme);

        for (int i = 0; i < PaletteColor::Low; ++i)
            inheritPaletteColor(newTheme, PaletteColor(i), suru->m_colors[newTheme][i], suru->m_customs[newTheme][i]);
    }
}

template <typename Enum>
static Enum toEnumValue(const QByteArray &value, bool *ok)
{
    QMetaEnum enumeration = QMetaEnum::fromType<Enum>();
    return static_cast<Enum>(enumeration.keyToValue(value, ok));
}

template <typename Enum>
static QByteArray toEnumKey(Enum key)
{
    QMetaEnum enumeration = QMetaEnum::fromType<Enum>();
    return enumeration.valueToKey(key);
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
        QSharedPointer<QSettings> settings = QQuickStylePrivate::settings(QStringLiteral("Suru"));

        bool ok = false;
        QByteArray themeValue = resolveSetting("QT_QUICK_CONTROLS_SURU_THEME", settings, QStringLiteral("Theme"));
        Theme themeEnum = toEnumValue<Theme>(themeValue, &ok);
        if (ok)
            globalTheme = m_theme = qquicksuru_effective_theme(themeEnum);
        else if (!themeValue.isEmpty())
            qWarning().nospace().noquote() << "Suru: unknown theme value: " << themeValue;
        else
            globalTheme = m_theme = qquicksuru_effective_theme(QQuickSuruStyle::System);

        initPaletteColor(Light, Positive, "QT_QUICK_CONTROLS_SURU_LIGHT_POSITIVE", settings);
        initPaletteColor(Light, Negative, "QT_QUICK_CONTROLS_SURU_LIGHT_NEGATIVE", settings);
        initPaletteColor(Light, Warning, "QT_QUICK_CONTROLS_SURU_LIGHT_WARNING", settings);
        initPaletteColor(Light, Information, "QT_QUICK_CONTROLS_SURU_LIGHT_INFORMATION", settings);
        initPaletteColor(Light, High, "QT_QUICK_CONTROLS_SURU_LIGHT_HIGH", settings);
        initPaletteColor(Light, MidHigh, "QT_QUICK_CONTROLS_SURU_LIGHT_MIDHIGH", settings);
        initPaletteColor(Light, Mid, "QT_QUICK_CONTROLS_SURU_LIGHT_MID", settings);
        initPaletteColor(Light, MidLow, "QT_QUICK_CONTROLS_SURU_LIGHT_MIDLOW", settings);
        initPaletteColor(Light, Low, "QT_QUICK_CONTROLS_SURU_LIGHT_LOW", settings);

        initPaletteColor(Dark, Positive, "QT_QUICK_CONTROLS_SURU_DARK_POSITIVE", settings);
        initPaletteColor(Dark, Negative, "QT_QUICK_CONTROLS_SURU_DARK_NEGATIVE", settings);
        initPaletteColor(Dark, Warning, "QT_QUICK_CONTROLS_SURU_DARK_WARNING", settings);
        initPaletteColor(Dark, Information, "QT_QUICK_CONTROLS_SURU_DARK_INFORMATION", settings);
        initPaletteColor(Dark, High, "QT_QUICK_CONTROLS_SURU_DARK_HIGH", settings);
        initPaletteColor(Dark, MidHigh, "QT_QUICK_CONTROLS_SURU_DARK_MIDHIGH", settings);
        initPaletteColor(Dark, Mid, "QT_QUICK_CONTROLS_SURU_DARK_MID", settings);
        initPaletteColor(Dark, MidLow, "QT_QUICK_CONTROLS_SURU_DARK_MIDLOW", settings);
        initPaletteColor(Dark, Low, "QT_QUICK_CONTROLS_SURU_DARK_LOW", settings);

        globalsInitialized = true;
    }

    QQuickAttachedObject::init(); // TODO: lazy init?
}

void QQuickSuruStyle::initPaletteColor(const Theme &theme, const PaletteColor &paletteColor,
                                     const QByteArray &env, QSharedPointer<QSettings> settings)
{
    QString name = QString::fromUtf8(toEnumKey<Theme>(theme)) + QString::fromUtf8(toEnumKey<PaletteColor>(paletteColor));

    QByteArray value = resolveSetting(env, settings, name);

    bool ok = false;
    Color colorEnum = toEnumValue<Color>(value, &ok);

    if (ok) {
        globalCustoms[theme][paletteColor] = m_customs[theme][paletteColor] = false;
        globalColors[theme][paletteColor] = m_colors[theme][paletteColor] = qquicksuru_color(colorEnum);
    } else if (!value.isEmpty()) {
        QColor color(value.constData());
        if (color.isValid()) {
            globalCustoms[theme][paletteColor] = m_customs[theme][paletteColor] = true;
            globalColors[theme][paletteColor] = m_colors[theme][paletteColor] = color.rgba();
        } else {
            qWarning().nospace().noquote() << "Suru: unknown " << name << " value: " << value;
        }
    }
}

bool QQuickSuruStyle::setPaletteColor(const QVariant &value, const QQuickSuruStyle::Theme &theme, const QQuickSuruStyle::PaletteColor &paletteColor)
{
    QRgb newValue = 0;
    bool custom = false;

    QString name = QString::fromUtf8(toEnumKey<Theme>(theme)).toLower() + QString::fromUtf8(toEnumKey<PaletteColor>(paletteColor));

    if (value.type() == QVariant::Int) {
        int val = value.toInt();
        if (val < Black || val > LightRed) {
            qmlInfo(parent()) << "unknown Suru." << name << " value: " << val;
            return false;
        }
        newValue = qquicksuru_color(static_cast<Color>(val));
    } else {
        int val = QMetaEnum::fromType<Color>().keyToValue(value.toByteArray());
        if (val != -1) {
            newValue = qquicksuru_color(static_cast<Color>(val));
        } else {
            QColor color(value.toString());
            if (!color.isValid()) {
                qmlInfo(parent()) << "unknown Suru." << name << " value: " << value.toString();
                return false;
            }

            custom = true;
            newValue = color.rgba();
        }
    }

    m_explicits[theme][paletteColor] = true;
    if (m_colors[theme][paletteColor] == newValue)
        return false;

    m_customs[theme][paletteColor] = custom;
    m_colors[theme][paletteColor] = newValue;

    propagatePaletteColor(theme, paletteColor);
    emit paletteChanged();

    return true;
}
