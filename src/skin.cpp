#include "skin.h"
#include "dsettings.h"
#include <QGuiApplication>
#include <QStyleHints>

Skin::Skin(QObject *parent)
    : QObject(parent)
{
}

QString Skin::getSkin(const QString &key)
{
    Q_UNUSED(key)
    return QString();
}

void Skin::setSkin(const QString &key)
{
    DSettings config;
    if (key == "dark") {
        QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Dark);
        config.setOption("theme", "dark");
    } else if (key == "light") {
        QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Light);
        config.setOption("theme", "light");
    } else {
        QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Unknown);
        config.setOption("theme", "system");
    }
}
