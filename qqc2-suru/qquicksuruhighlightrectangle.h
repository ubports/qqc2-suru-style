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

#ifndef QQUICKSURUHIGHLIGHTRECTANGLE_H
#define QQUICKSURUHIGHLIGHTRECTANGLE_H

#include <QtQuick/qquickpainteditem.h>

class QQuickSuruHighlightRectangle : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor MEMBER m_backgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor borderColor MEMBER m_borderColor NOTIFY borderColorChanged)
    Q_PROPERTY(qreal backgroundOpacity MEMBER m_backgroundOpacity NOTIFY backgroundOpacityChanged)

public:
    QQuickSuruHighlightRectangle(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

Q_SIGNALS:
    void backgroundColorChanged();
    void borderColorChanged();
    void backgroundOpacityChanged();

private:
    QColor m_backgroundColor;
    QColor m_borderColor;
    qreal m_backgroundOpacity;
};

#endif // QQUICKSURUHIGHLIGHTRECTANGLE_H
