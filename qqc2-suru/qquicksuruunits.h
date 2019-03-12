#ifndef QQUICKSURUUNITS_H
#define QQUICKSURUUNITS_H

#include <QtCore/qobject.h>
#include <QtGui/qfont.h>

class QQuickSuruUnits : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int breakpointXSmall READ breakpointXSmall CONSTANT)
    Q_PROPERTY(int breakpointSmall READ breakpointSmall CONSTANT)
    Q_PROPERTY(int breakpointMedium READ breakpointMedium CONSTANT)
    Q_PROPERTY(int breakpointLarge READ breakpointLarge CONSTANT)

    Q_PROPERTY(QFont fontHeadingOne READ fontHeadingOne NOTIFY fontsChanged)
    Q_PROPERTY(QFont fontHeadingTwo READ fontHeadingTwo NOTIFY fontsChanged)
    Q_PROPERTY(QFont fontHeadingThree READ fontHeadingThree NOTIFY fontsChanged)
    Q_PROPERTY(QFont fontParagraph READ fontParagraph NOTIFY fontsChanged)
    Q_PROPERTY(QFont fontSmall READ fontSmall NOTIFY fontsChanged)
    Q_PROPERTY(QFont fontCaption READ fontCaption NOTIFY fontsChanged)
    Q_PROPERTY(QFont fontCodeBlock READ fontCodeBlock NOTIFY fontsChanged)

public:
    explicit QQuickSuruUnits(QObject *parent = 0);

    // Breakpoints for responsive UI
    int breakpointXSmall() const    { return gu(56); }
    int breakpointSmall() const     { return gu(80); }
    int breakpointMedium() const    { return gu(96); }
    int breakpointLarge() const     { return gu(128); }

    const QFont &fontHeadingOne() const { return m_headingOne; }
    const QFont &fontHeadingTwo() const { return m_headingTwo; }
    const QFont &fontHeadingThree() const { return m_headingThree; }
    const QFont &fontParagraph() const { return m_paragraph; }
    const QFont &fontSmall() const { return m_small; }
    const QFont &fontCaption() const { return m_caption; }
    const QFont &fontCodeBlock() const { return m_codeBlock; }

    // 1 rem * 0.5 = 8px. Used for convenience.
    Q_INVOKABLE int gu(qreal value) const;

    // Used for font-indipendent sizes. = 1 px
    Q_INVOKABLE int dp(qreal value) const;

    // The size of the paragraph font, in px. = 16 px
    Q_INVOKABLE int rem(qreal value) const;

    Q_INVOKABLE int applyLabelTopPadding(const int previousBlockLevel) const;

signals:
    void fontsChanged();

private:
    void setupFonts();

    QFont m_headingOne;
    QFont m_headingTwo;
    QFont m_headingThree;
    QFont m_paragraph;
    QFont m_small;
    QFont m_caption;
    QFont m_codeBlock;

    float m_devicePixelRatio;
    float m_gridUnit;
};

#endif // QQUICKSURUUNITS_H
