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

#include <QtQuickControls2/private/qquickstyleplugin_p.h>

#include "qquicksurustyle_p.h"
#include "qquicksurutheme_p.h"
//#include "qquicksuruanimation_p.h"
//#include "qquicksuruunits_p.h"
#include "qquicksuruhighlightrectangle.h"

#include <QtQuickControls2/private/qquickcolorimageprovider_p.h>

static inline void initResources()
{
    Q_INIT_RESOURCE(qtquickcontrols2surustyleplugin);
#ifdef QT_STATIC
    Q_INIT_RESOURCE(qmake_QtQuick_Controls_2_Suru);
#endif
}

QT_BEGIN_NAMESPACE

class QtQuickControls2SuruStylePlugin: public QQuickStylePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtQuickControls2SuruStylePlugin(QObject *parent = nullptr);

    void registerTypes(const char *uri) override;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;

    QString name() const override;
    QQuickProxyTheme *createTheme() const override;
};

QtQuickControls2SuruStylePlugin::QtQuickControls2SuruStylePlugin(QObject *parent) : QQuickStylePlugin(parent)
{
    initResources();
}

void QtQuickControls2SuruStylePlugin::registerTypes(const char *uri)
{
    qmlRegisterUncreatableType<QQuickSuruStyle>(uri, 2, 2, "Suru", tr("Suru is an attached property"));
    //qmlRegisterUncreatableType<QQuickSuruAnimation>(uri, 2, 2, "Animation", tr("Use Suru attached property instead"));
    //qmlRegisterUncreatableType<QQuickSuruUnits>(uri, 2, 2, "Units", tr("Use Suru attached property instead"));
    qmlRegisterType<QQuickSuruHighlightRectangle>(uri, 2, 2, "HighlightRectangle");

}

void QtQuickControls2SuruStylePlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQuickStylePlugin::initializeEngine(engine, uri);

    engine->addImageProvider(name(), new QQuickColorImageProvider(QStringLiteral(":/qt-project.org/imports/QtQuick/Controls.2/Suru/assets")));
}

QString QtQuickControls2SuruStylePlugin::name() const
{
    return QStringLiteral("suru");
}

QQuickProxyTheme *QtQuickControls2SuruStylePlugin::createTheme() const
{
    return new QQuickSuruTheme;
}

QT_END_NAMESPACE

#include "qtquickcontrols2surustyleplugin.moc"
