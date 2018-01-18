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

#include "qquicksuruhighlightrectangle.h"

#include <QtGui/qpixmap.h>
#include <QtGui/qpainter.h>
#include <QtGui/qpixmapcache.h>
#include <QtQuick/private/qquickitem_p.h>

QQuickSuruHighlightRectangle::QQuickSuruHighlightRectangle(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    QQuickItemPrivate::get(this)->setTransparentForPositioner(true);

    connect(this, &QQuickSuruHighlightRectangle::borderColorChanged, [=]() { this->update(); });
    connect(this, &QQuickSuruHighlightRectangle::backgroundColorChanged, [=]() { this->update(); });
    connect(this, &QQuickSuruHighlightRectangle::backgroundOpacityChanged, [=]() { this->update(); });
    connect(this, &QQuickSuruHighlightRectangle::visibleChanged, [=]() { this->update(); });
}

void QQuickSuruHighlightRectangle::paint(QPainter *painter)
{
    if (!isVisible() || width() <= 0 || height() <= 0)
        return;

    QRect bounds = boundingRect().toAlignedRect();
    const int boundsWidth = bounds.width();
    const int boundsHeight = bounds.height();

    const QString key = QStringLiteral("qquicksuruhighlightrectangle_%1_%2_%3_%4_%5").arg(QString::number(boundsWidth),
                                                                                          QString::number(boundsHeight),
                                                                                          m_backgroundColor.name(),
                                                                                          m_borderColor.name(),
                                                                                          QString::number(m_backgroundOpacity));

    QPixmap pixmap(boundsWidth, boundsHeight);
    if (!QPixmapCache::find(key, &pixmap)) {
        const QColor color = QColor::fromRgbF(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), m_backgroundOpacity);

        bounds.adjust(0, -1, -1, -1);
        pixmap.fill(color);
        QPainter p(&pixmap);

        QPen pen;
        pen.setWidth(1);
        pen.setColor(m_borderColor);
        p.setPen(pen);
        p.drawRect(bounds);

        QPixmapCache::insert(key, pixmap);
    }
    painter->drawPixmap(0, 0, pixmap);
}
