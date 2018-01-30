#include "qquicksuruunits.h"
#include "qquicksurustyle_p.h"

#include <QtGui/qfontinfo.h>

#define SURU_FONT_SIZE_MULTIPLIER 0.875

QQuickSuruUnits::QQuickSuruUnits(QObject *parent) : QObject(parent)
{
    m_headingOne.setPixelSize(32 * SURU_FONT_SIZE_MULTIPLIER);
    m_headingOne.setWeight(QFont::Light);

    m_headingTwo.setPixelSize(24 * SURU_FONT_SIZE_MULTIPLIER);
    m_headingTwo.setWeight(QFont::Light);

    m_headingThree.setPixelSize(22 * SURU_FONT_SIZE_MULTIPLIER);
    m_headingThree.setWeight(QFont::Light);

    m_paragraph.setPixelSize(16 * SURU_FONT_SIZE_MULTIPLIER);
    m_paragraph.setWeight(QFont::Light);

    m_small.setPixelSize(14 * SURU_FONT_SIZE_MULTIPLIER);
    m_small.setWeight(QFont::Light);

    m_caption.setPixelSize(14 * SURU_FONT_SIZE_MULTIPLIER);
    m_caption.setWeight(QFont::Light);
    m_caption.setItalic(true);

    m_codeBlock.setPixelSize(16 * SURU_FONT_SIZE_MULTIPLIER);
    m_codeBlock.setWeight(QFont::Light);

    const QFont font(QLatin1String("Ubuntu"));
    if (QFontInfo(font).family() == QLatin1String("Ubuntu")) {
        const QString family = font.family();

       m_headingOne.setFamily(family);
       m_headingTwo.setFamily(family);
       m_headingThree.setFamily(family);
       m_paragraph.setFamily(family);
       m_small.setFamily(family);
       m_caption.setFamily(family);
    }

    const QFont monoFont(QLatin1String("Ubuntu Mono"));
    if (QFontInfo(monoFont).family() == QLatin1String("Ubuntu Mono")) {
        const QString family = monoFont.family();
        m_codeBlock.setFamily(family);
    }
}

int QQuickSuruUnits::gu(qreal value) const
{
    return value * 8;
}

int QQuickSuruUnits::dp(int value) const
{
    return value;
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
