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

#ifndef QQUICKSURUSTYLE_P_H
#define QQUICKSURUSTYLE_P_H

#include <QSettings>
#include <QtGui/qcolor.h>
#include <QtQuickControls2/private/qquickattachedobject_p.h>

#define SURU_PALETTE_COLOR(name, theme, palettecolor) \
    Q_PROPERTY(QVariant name READ name WRITE set##name RESET reset##name NOTIFY paletteChanged FINAL) \
    public: \
        QVariant name() const { return QColor::fromRgba(m_colors[ theme ][ palettecolor ]); } \
        void set##name(const QVariant &value) { setPaletteColor(value, theme, palettecolor ); } \
        void reset##name() { resetPaletteColor( theme, palettecolor ); } \
    private:


class QQuickSuruAnimations;
class QQuickSuruUnits;

class QQuickSuruStyle : public QQuickAttachedObject
{
    Q_OBJECT

    // Light or dark theme
    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged FINAL)

    SURU_PALETTE_COLOR(lightPositive, Light, Positive)
    SURU_PALETTE_COLOR(lightNegative, Light, Negative)
    SURU_PALETTE_COLOR(lightWarning, Light, Warning)
    SURU_PALETTE_COLOR(lightInformation, Light, Information)
    SURU_PALETTE_COLOR(lightHigh, Light, High)
    SURU_PALETTE_COLOR(lightMidHigh, Light, MidHigh)
    SURU_PALETTE_COLOR(lightMid, Light, Mid)
    SURU_PALETTE_COLOR(lightMidLow, Light, MidLow)
    SURU_PALETTE_COLOR(lightLow, Light, Low)

    SURU_PALETTE_COLOR(darkPositive, Dark, Positive)
    SURU_PALETTE_COLOR(darkNegative, Dark, Negative)
    SURU_PALETTE_COLOR(darkWarning, Dark, Warning)
    SURU_PALETTE_COLOR(darkInformation, Dark, Information)
    SURU_PALETTE_COLOR(darkHigh, Dark, High)
    SURU_PALETTE_COLOR(darkMidHigh, Dark, MidHigh)
    SURU_PALETTE_COLOR(darkMid, Dark, Mid)
    SURU_PALETTE_COLOR(darkMidLow, Dark, MidLow)
    SURU_PALETTE_COLOR(darkLow, Dark, Low)

    // Can be used where 'highlighted' property is provided. It's not propagated to children.
    // When set, 'highlightColor' property returns {positive|negative|warning|information} color, as defined in Suru palettes.
    // Default is Highlight. If unset, it's InformationHighlight as well
    Q_PROPERTY(HighlightType highlightType READ highlightType WRITE setHighlightType RESET resetHighlightType NOTIFY highlightTypeChanged FINAL)

    Q_PROPERTY(TextLevel textLevel READ textLevel WRITE setTextLevel RESET resetTextLevel NOTIFY textLevelChanged FINAL)
    Q_PROPERTY(TextStyle textStyle READ textStyle WRITE setTextStyle RESET resetTextStyle NOTIFY textStyleChanged FINAL)

    // Colors as result from 'theme' + '{dark|light}Palette' properties
    Q_PROPERTY(QColor highlightColor READ highlightColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor activeFocusColor READ activeFocusColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor overlayColor READ overlayColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor neutralColor READ neutralColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor secondaryBackgroundColor READ secondaryBackgroundColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QQuickSuruAnimations* animations READ animations CONSTANT)
    Q_PROPERTY(QQuickSuruUnits* units READ units CONSTANT)

public:
    enum Theme {
        Light, Dark, System
    };
    Q_ENUM(Theme)

    enum HighlightType {
        PositiveHighlight,
        NegativeHighlight,
        WarningHighlight,
        InformationHighlight
    };
    Q_ENUM(HighlightType)

    enum Color {
        Black, Jet, Inkstone, Graphite,
        Ash, Silk, Porcelain, White,
        Blue, Green, Red, Yellow,
        Orange, Purple,
        LightBlue, LightGreen, LightYellow, LightRed
    };
    Q_ENUM(Color)

    enum PaletteColor {
        Positive, Negative, Warning, Information,
        High, MidHigh, Mid, MidLow, Low
    };
    Q_ENUM(PaletteColor)

    enum TextLevel {
        HeadingOne, HeadingTwo, HeadingThree,
        Paragraph, Small, Caption, CodeBlock
    };
    Q_ENUM(TextLevel)

    enum TextStyle {
        PrimaryText, SecondaryText, TertiaryText
    };
    Q_ENUM(TextStyle)

    explicit QQuickSuruStyle(QObject *parent = nullptr);

    static QQuickSuruStyle *qmlAttachedProperties(QObject *object);

    Theme theme() const;
    void setTheme(Theme theme);
    void inheritTheme(Theme theme);
    void propagateTheme();
    void resetTheme();

    HighlightType highlightType() const;
    void setHighlightType(HighlightType type);
    void resetHighlightType();

    TextLevel textLevel() const;
    void setTextLevel(TextLevel level);
    void resetTextLevel();

    TextStyle textStyle() const;
    void setTextStyle(TextStyle style);
    void resetTextStyle();

    QColor highlightColor() const;
    QColor activeFocusColor() const;
    QColor overlayColor() const;
    QColor foregroundColor() const;
    QColor neutralColor() const;
    QColor secondaryBackgroundColor() const;
    QColor backgroundColor() const;

    Q_INVOKABLE QColor color(Color color, qreal opacity = 1.0) const;

    QQuickSuruAnimations *animations() const { return m_animations; }
    QQuickSuruUnits *units() const { return m_units; }

Q_SIGNALS:
    void themeChanged();
    void highlightTypeChanged();
    void textLevelChanged();
    void textStyleChanged();
    void paletteChanged();

protected:
    void attachedParentChange(QQuickAttachedObject *newParent, QQuickAttachedObject *oldParent) override;

private:
    void init();

    void initPaletteColor(const Theme &theme, const PaletteColor &paletteColor, const QByteArray &env, QSharedPointer<QSettings> settings);
    bool setPaletteColor(const QVariant &value, const Theme &theme, const PaletteColor &paletteColor);
    void inheritPaletteColor(const Theme &theme, const PaletteColor &paletteColor, QRgb value, bool custom);
    void propagatePaletteColor(const Theme &theme, const PaletteColor &paletteColor);
    void resetPaletteColor(const Theme &theme, const PaletteColor &paletteColor);

    bool m_explicitTheme;
    QQuickSuruStyle::Theme m_theme;
    HighlightType m_highlightType;
    TextLevel m_textLevel;
    TextStyle m_textStyle;

    bool m_explicits[2][9];
    bool m_customs[2][9];
    QRgb m_colors[2][9];

    QQuickSuruAnimations *m_animations;
    QQuickSuruUnits *m_units;
};

QML_DECLARE_TYPEINFO(QQuickSuruStyle, QML_HAS_ATTACHED_PROPERTIES)

#endif // QQUICKSURUSTYLE_P_H
