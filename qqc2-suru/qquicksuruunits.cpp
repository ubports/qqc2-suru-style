#include "qquicksuruunits.h"
#include "qquicksurustyle_p.h"

#include <QtCore/QtMath>
#include <QtGui/qfontinfo.h>
#include <QtGui/QGuiApplication>
#include <QtGui/private/qhighdpiscaling_p.h>

#define SURU_FONT_SIZE_MULTIPLIER 0.875
#define ENV_GRID_UNIT_PX "GRID_UNIT_PX"
#define DEFAULT_GRID_UNIT_PX 8

static float getenvFloat(const char* name, float defaultValue)
{
    QByteArray stringValue = qgetenv(name);
    bool ok;
    float value = stringValue.toFloat(&ok);
    return ok ? value : defaultValue;
}

QQuickSuruUnits::QQuickSuruUnits(QObject *parent) :
    QObject(parent),
    m_devicePixelRatio(qGuiApp->devicePixelRatio())
{
    // TODO recalculate based on window/devicePixelRatio changes like the ubuntu uitk
    if (QHighDpiScaling::isActive())
      m_gridUnit = qCeil(DEFAULT_GRID_UNIT_PX * m_devicePixelRatio);
    else
      m_gridUnit = getenvFloat(ENV_GRID_UNIT_PX, DEFAULT_GRID_UNIT_PX * m_devicePixelRatio);

    setupFonts();
}

void QQuickSuruUnits::setupFonts()
{
    m_headingOne.setPixelSize(dp(32) * SURU_FONT_SIZE_MULTIPLIER);
    m_headingOne.setWeight(QFont::Light);

    m_headingTwo.setPixelSize(dp(24) * SURU_FONT_SIZE_MULTIPLIER);
    m_headingTwo.setWeight(QFont::Light);

    m_headingThree.setPixelSize(dp(22) * SURU_FONT_SIZE_MULTIPLIER);
    m_headingThree.setWeight(QFont::Light);

    m_paragraph.setPixelSize(dp(16) * SURU_FONT_SIZE_MULTIPLIER);
    m_paragraph.setWeight(QFont::Light);

    m_small.setPixelSize(dp(14) * SURU_FONT_SIZE_MULTIPLIER);
    m_small.setWeight(QFont::Light);

    m_caption.setPixelSize(dp(14) * SURU_FONT_SIZE_MULTIPLIER);
    m_caption.setWeight(QFont::Light);
    m_caption.setItalic(true);

    m_codeBlock.setPixelSize(dp(16) * SURU_FONT_SIZE_MULTIPLIER);
    m_codeBlock.setWeight(QFont::Light);

    const QFont font(QStringLiteral("Ubuntu"));
    if (QFontInfo(font).family() == QStringLiteral("Ubuntu")) {
        const QString family = font.family();

       m_headingOne.setFamily(family);
       m_headingTwo.setFamily(family);
       m_headingThree.setFamily(family);
       m_paragraph.setFamily(family);
       m_small.setFamily(family);
       m_caption.setFamily(family);
    }

    const QFont monoFont(QStringLiteral("Ubuntu Mono"));
    if (QFontInfo(monoFont).family() == QStringLiteral("Ubuntu Mono")) {
        const QString family = monoFont.family();
        m_codeBlock.setFamily(family);
    }

    emit fontsChanged();
}

int QQuickSuruUnits::gu(qreal value) const
{
    return qRound(value * m_gridUnit) / m_devicePixelRatio;
}

int QQuickSuruUnits::dp(qreal value) const
{
    const qreal ratio = m_gridUnit / DEFAULT_GRID_UNIT_PX;
    if (value <= 2.0) {
        // for values under 2dp, return only multiples of the value
        return qRound(value * qFloor(ratio)) / m_devicePixelRatio;
    } else {
        return qRound(value * ratio) / m_devicePixelRatio;
    }
}

int QQuickSuruUnits::rem(qreal value) const
{
    return value * qreal(m_paragraph.pixelSize());
}

int QQuickSuruUnits::applyLabelTopPadding(const int previousBlockLevel = QQuickSuruStyle::Paragraph) const
{
    int prevBlockLevel = previousBlockLevel;

    if (prevBlockLevel < QQuickSuruStyle::HeadingOne || prevBlockLevel > QQuickSuruStyle::CodeBlock) {
        prevBlockLevel = QQuickSuruStyle::Paragraph;
    }

    QQuickSuruStyle *style = qobject_cast<QQuickSuruStyle*>(this->parent());
    if (style) {
        switch (style->textLevel()) {
        case QQuickSuruStyle::HeadingOne:
            return rem(2);
        case QQuickSuruStyle::HeadingTwo:
        case QQuickSuruStyle::HeadingThree:
            return rem(1.5);
        case QQuickSuruStyle::Paragraph:
            return (prevBlockLevel == QQuickSuruStyle::HeadingOne
                    || prevBlockLevel == QQuickSuruStyle::Paragraph) ? rem(1) : rem(0.5);
        case QQuickSuruStyle::Small:
        case QQuickSuruStyle::Caption:
            return rem(1);
        case QQuickSuruStyle::CodeBlock:
            return rem(1.25);
        default:    // Likely, we'll never get here.
            return 0;
        }
    }

    return 0;
}
