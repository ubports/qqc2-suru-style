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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/qcolor.h>
#include <QtQuickControls2/private/qquickstyleattached_p.h>

QT_BEGIN_NAMESPACE

class QQuickSuruStylePrivate;

class QQuickSuruStyle : public QQuickStyleAttached
{
    Q_OBJECT
    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged FINAL)

    Q_PROPERTY(QVariant accent READ accent WRITE setAccent RESET resetAccent NOTIFY accentChanged FINAL)
    Q_PROPERTY(QVariant positive READ positive WRITE setPositive RESET resetPositive NOTIFY positiveChanged FINAL)
    Q_PROPERTY(QVariant negative READ negative WRITE setNegative RESET resetNegative NOTIFY negativeChanged FINAL)
    Q_PROPERTY(QVariant warning READ warning WRITE setWarning RESET resetWarning NOTIFY warningChanged FINAL)
    Q_PROPERTY(QVariant information READ information WRITE setInformation RESET resetInformation NOTIFY informationChanged FINAL)

    Q_PROPERTY(QVariant lightHigh READ lightHigh WRITE setLightHigh RESET resetLightHigh NOTIFY lightHighChanged FINAL)
    Q_PROPERTY(QVariant lightMidHigh READ lightMidHigh WRITE setLightMidHigh RESET resetLightMidHigh NOTIFY lightMidHighChanged FINAL)
    Q_PROPERTY(QVariant lightMid READ lightMid WRITE setLightMid RESET resetLightMid NOTIFY lightMidChanged FINAL)
    Q_PROPERTY(QVariant lightMidLow READ lightMidLow WRITE setLightMidLow RESET resetLightMidLow NOTIFY lightMidLowChanged FINAL)
    Q_PROPERTY(QVariant lightLow READ lightLow WRITE setLightLow RESET resetLightLow NOTIFY lightLowChanged FINAL)

    Q_PROPERTY(QVariant darkHigh READ darkHigh WRITE setDarkHigh RESET resetDarkHigh NOTIFY darkHighChanged FINAL)
    Q_PROPERTY(QVariant darkMidHigh READ darkMidHigh WRITE setDarkMidHigh RESET resetDarkMidHigh NOTIFY darkMidHighChanged FINAL)
    Q_PROPERTY(QVariant darkMid READ darkMid WRITE setDarkMid  RESET resetDarkMid NOTIFY darkMidChanged FINAL)
    Q_PROPERTY(QVariant darkMidLow READ darkMidLow WRITE setDarkMidLow RESET resetDarkMidLow NOTIFY darkMidLowChanged FINAL)
    Q_PROPERTY(QVariant darkLow READ darkLow WRITE setDarkLow RESET resetDarkLow NOTIFY darkLowChanged FINAL)

    Q_PROPERTY(QColor accentColor READ accentColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor positiveColor READ positiveColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor negativeColor READ negativeColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor warningColor READ warningColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor informationColor READ informationColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor secondaryForegroundColor READ secondaryForegroundColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor neutralColor READ neutralColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor secondaryBackgroundColor READ secondaryBackgroundColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor NOTIFY paletteChanged FINAL)


    // TODO: QQuickSuruUnits
    // Q_PROPERTY(QQuickSuruUnits* units READ units CONSTANT)

    // TODO: QQuickSuruAnimation
    // Q_PROPERTY(QQuickSuruAnimation* animation READ animation CONSTANT)

public:
    enum Theme { Light, Dark, System };
    Q_ENUM(Theme)

    enum Color {
        White, Porcelain, Silk, Ash,
        Jet, Inkstone, Slate, Graphite,
        Blue, Green, Yellow, Orange, Red, Purple
    };
    Q_ENUM(Color)

    enum Shade {
        Shade50,
        Shade100,
        Shade200,
        Shade300,
        Shade400,
        Shade500,
        Shade600,
        Shade700,
        Shade800,
        Shade900,
    };
    Q_ENUM(Shade)

    explicit QQuickSuruStyle(QObject *parent = nullptr);

    static QQuickSuruStyle *qmlAttachedProperties(QObject *object);

    Theme theme() const;
    void setTheme(Theme theme);
    void inheritTheme(Theme theme);
    void propagateTheme();
    void resetTheme();

    QVariant accent() const;
    void setAccent(const QVariant &accent);
    void inheritAccent(QRgb accent, bool custom);
    void propagateAccent();
    void resetAccent();

    QVariant positive() const;
    void setPositive(const QVariant &positive);
    void inheritPositive(QRgb positive, bool custom);
    void propagatePositive();
    void resetPositive();

    QVariant negative() const;
    void setNegative(const QVariant &negative);
    void inheritNegative(QRgb negative, bool custom);
    void propagateNegative();
    void resetNegative();

    QVariant warning() const;
    void setWarning(const QVariant &warning);
    void inheritWarning(QRgb warning, bool custom);
    void propagateWarning();
    void resetWarning();

    QVariant information() const;
    void setInformation(const QVariant &information);
    void inheritInformation(QRgb information, bool custom);
    void propagateInformation();
    void resetInformation();

    QVariant lightHigh() const;
    void setLightHigh(const QVariant &lightHigh);
    void inheritLightHigh(QRgb lightHigh, bool custom);
    void propagateLightHigh();
    void resetLightHigh();

    QVariant lightMidHigh() const;
    void setLightMidHigh(const QVariant &lightMidHigh);
    void inheritLightMidHigh(QRgb lightMidHigh, bool custom);
    void propagateLightMidHigh();
    void resetLightMidHigh();

    QVariant lightMid() const;
    void setLightMid(const QVariant &lightMid);
    void inheritLightMid(QRgb lightMid, bool custom);
    void propagateLightMid();
    void resetLightMid();

    QVariant lightMidLow() const;
    void setLightMidLow(const QVariant &lightMidLow);
    void inheritLightMidLow(QRgb lightMidLow, bool custom);
    void propagateLightMidLow();
    void resetLightMidLow();

    QVariant lightLow() const;
    void setLightLow(const QVariant &lightLow);
    void inheritLightLow(QRgb lightLow, bool custom);
    void propagateLightLow();
    void resetLightLow();

    QVariant darkHigh() const;
    void setDarkHigh(const QVariant &darkHigh);
    void inheritDarkHigh(QRgb darkHigh, bool custom);
    void propagateDarkHigh();
    void resetDarkHigh();

    QVariant darkMidHigh() const;
    void setDarkMidHigh(const QVariant &darkMidHigh);
    void inheritDarkMidHigh(QRgb darkMidHigh, bool custom);
    void propagateDarkMidHigh();
    void resetDarkMidHigh();

    QVariant darkMid() const;
    void setDarkMid(const QVariant &darkMid);
    void inheritDarkMid(QRgb darkMid, bool custom);
    void propagateDarkMid();
    void resetDarkMid();

    QVariant darkMidLow() const;
    void setDarkMidLow(const QVariant &darkMidLow);
    void inheritDarkMidLow(QRgb darkMidLow, bool custom);
    void propagateDarkMidLow();
    void resetDarkMidLow();

    QVariant darkLow() const;
    void setDarkLow(const QVariant &darkLow);
    void inheritDarkLow(QRgb darkLow, bool custom);
    void propagateDarkLow();
    void resetDarkLow();

    QColor accentColor() const;
    QColor positiveColor() const;
    QColor negativeColor() const;
    QColor warningColor() const;
    QColor informationColor() const;
    QColor foregroundColor() const;
    QColor secondaryForegroundColor() const;
    QColor neutralColor() const;
    QColor secondaryBackgroundColor() const;
    QColor backgroundColor() const;

    // QQuickSuruUnits* units() const { return m_units; }
    //QQuickSuruAnimation* animation() const { return m_animation; }

    Q_INVOKABLE QColor color(Color color) const;

    Q_INVOKABLE bool isLightColor(const QColor &color) const {
        return color.lightnessF() > .85;
    }

Q_SIGNALS:
    void themeChanged();

    void accentChanged();
    void positiveChanged();
    void negativeChanged();
    void warningChanged();
    void informationChanged();

    void lightHighChanged();
    void lightMidHighChanged();
    void lightMidChanged();
    void lightMidLowChanged();
    void lightLowChanged();

    void darkHighChanged();
    void darkMidHighChanged();
    void darkMidChanged();
    void darkMidLowChanged();
    void darkLowChanged();

    void paletteChanged();

protected:
    void parentStyleChange(QQuickStyleAttached *newParent, QQuickStyleAttached *oldParent) override;

private:
    void init();
    bool variantToRgba(const QVariant &var, const char *name, QRgb *rgba, bool *custom) const;
    void solveSuruColor(bool &globalCustom, bool &localCustom, QRgb &globalColor, QRgb &localColor, const QByteArray &env, QSharedPointer<QSettings> settings, const QString &name) const;


    // These reflect whether a color value was explicitly set on the specific
    // item that this attached style object represents.
    bool m_explicitTheme;
    bool m_explicitAccent;
    bool m_explicitPositive;
    bool m_explicitNegative;
    bool m_explicitWarning;
    bool m_explicitInformation;

    bool m_explicitLightHigh;
    bool m_explicitLightMidHigh;
    bool m_explicitLightMid;
    bool m_explicitLightMidLow;
    bool m_explicitLightLow;

    bool m_explicitDarkHigh;
    bool m_explicitDarkMidHigh;
    bool m_explicitDarkMid;
    bool m_explicitDarkMidLow;
    bool m_explicitDarkLow;

    // These reflect whether the color value that was either inherited or
    // explicitly set is in the form that QColor expects, rather than one of
    // our pre-defined color enum values.
    bool m_customAccent;
    bool m_customPositive;
    bool m_customNegative;
    bool m_customWarning;
    bool m_customInformation;

    bool m_customLightHigh;
    bool m_customLightMidHigh;
    bool m_customLightMid;
    bool m_customLightMidLow;
    bool m_customLightLow;

    bool m_customDarkHigh;
    bool m_customDarkMidHigh;
    bool m_customDarkMid;
    bool m_customDarkMidLow;
    bool m_customDarkLow;

    // These will be true when this item has an explicit or inherited foreground/background
    // color, or these colors were declared globally via settings (e.g. conf or env vars).
    // Some color properties of the style will return different values depending on whether
    // or not these are set.
    bool m_hasAccent;
    bool m_hasPositive;
    bool m_hasNegative;
    bool m_hasWarning;
    bool m_hasInformation;

    bool m_hasLightHigh;
    bool m_hasLightMidHigh;
    bool m_hasLightMid;
    bool m_hasLightMidLow;
    bool m_hasLightLow;

    bool m_hasDarkHigh;
    bool m_hasDarkMidHigh;
    bool m_hasDarkMid;
    bool m_hasDarkMidLow;
    bool m_hasDarkLow;

    // The actual values for this item, whether explicit, inherited or globally set.
    QQuickSuruStyle::Theme m_theme;

    QRgb m_accent;
    QRgb m_positive;
    QRgb m_negative;
    QRgb m_warning;
    QRgb m_information;

    QRgb m_lightHigh;
    QRgb m_lightMidHigh;
    QRgb m_lightMid;
    QRgb m_lightMidLow;
    QRgb m_lightLow;

    QRgb m_darkHigh;
    QRgb m_darkMidHigh;
    QRgb m_darkMid;
    QRgb m_darkMidLow;
    QRgb m_darkLow;

    //QQuickSuruUnits* m_units;
    //QQuickSuruAnimation* m_animation;
};

QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QQuickSuruStyle, QML_HAS_ATTACHED_PROPERTIES)

#endif // QQUICKSURUSTYLE_P_H
