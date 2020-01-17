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
#include "qquicksuruanimations.h"
#include "qquicksuruunits.h"

#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
#include <QQmlEngine>
#else
#include <QtQuickControls2/private/qquickcolorimageprovider_p.h>

static inline void initResources()
{
    Q_INIT_RESOURCE(qtquickcontrols2surustyleplugin);
#ifdef QT_STATIC
    Q_INIT_RESOURCE(qmake_QtQuick_Controls_2_Suru);
#endif
}
#endif

class QtQuickControls2SuruStylePlugin: public QQuickStylePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtQuickControls2SuruStylePlugin(QObject *parent = nullptr);

    void registerTypes(const char *uri) override;
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
#else
    void initializeEngine(QQmlEngine *engine, const char *uri) override;
#endif

    QString name() const override;
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    void initializeTheme(QQuickTheme *theme) override;
#else
    QQuickProxyTheme *createTheme() const override;
#endif
};

QtQuickControls2SuruStylePlugin::QtQuickControls2SuruStylePlugin(QObject *parent) : QQuickStylePlugin(parent)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
#else
    initResources();
#endif
}

void QtQuickControls2SuruStylePlugin::registerTypes(const char *uri)
{
    qmlRegisterModule(uri, 2, 2);
    qmlRegisterUncreatableType<QQuickSuruStyle>(uri, 2, 2, "Suru", tr("Suru is an attached property"));

    qmlRegisterType<QQuickSuruAnimations>();
    qmlRegisterType<QQuickSuruUnits>();
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    qmlRegisterType(resolvedUrl(QStringLiteral("CheckIndicator.qml")), uri, 2, 0, "CheckIndicator");
    qmlRegisterType(resolvedUrl(QStringLiteral("CursorDelegate.qml")), uri, 2, 0, "CursorDelegate");
    qmlRegisterType(resolvedUrl(QStringLiteral("ElevationEffect.qml")), uri, 2, 0, "ElevationEffect");
    qmlRegisterType(resolvedUrl(QStringLiteral("HighlightFocusRectangle.qml")), uri, 2, 0, "HighlightFocusRectangle");
    qmlRegisterType(resolvedUrl(QStringLiteral("Label.qml")), uri, 2, 0, "Label");
    qmlRegisterType(resolvedUrl(QStringLiteral("RadioIndicator.qml")), uri, 2, 0, "RadioIndicator");
    qmlRegisterType(resolvedUrl(QStringLiteral("SwitchIndicator.qml")), uri, 2, 0, "SwitchIndicator");
#else
    qmlRegisterType(typeUrl(QStringLiteral("CheckIndicator.qml")), uri, 2, 0, "CheckIndicator");
    qmlRegisterType(typeUrl(QStringLiteral("CursorDelegate.qml")), uri, 2, 0, "CursorDelegate");
    qmlRegisterType(typeUrl(QStringLiteral("ElevationEffect.qml")), uri, 2, 0, "ElevationEffect");
    qmlRegisterType(typeUrl(QStringLiteral("HighlightFocusRectangle.qml")), uri, 2, 0, "HighlightFocusRectangle");
    qmlRegisterType(typeUrl(QStringLiteral("Label.qml")), uri, 2, 0, "Label");
    qmlRegisterType(typeUrl(QStringLiteral("RadioIndicator.qml")), uri, 2, 0, "RadioIndicator");
    qmlRegisterType(typeUrl(QStringLiteral("SwitchIndicator.qml")), uri, 2, 0, "SwitchIndicator");
#endif

}

#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
#else
void QtQuickControls2SuruStylePlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQuickStylePlugin::initializeEngine(engine, uri);

    engine->addImageProvider(name(), new QQuickColorImageProvider(QStringLiteral(":/qt-project.org/imports/QtQuick/Controls.2/Suru/assets")));
}
#endif

QString QtQuickControls2SuruStylePlugin::name() const
{
    return QStringLiteral("suru");
}

#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
void QtQuickControls2SuruStylePlugin::initializeTheme(QQuickTheme *theme)
{
    QQuickSuruTheme::initialize(theme);
}
#else
QQuickProxyTheme *QtQuickControls2SuruStylePlugin::createTheme() const
{
    return new QQuickSuruTheme;
}
#endif

#include "qtquickcontrols2surustyleplugin.moc"
