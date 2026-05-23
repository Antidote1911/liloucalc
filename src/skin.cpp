#include "skin.h"
#include "dsettings.h"
#include <QApplication>
#include <QGuiApplication>
#include <QStyleHints>
#include <QPalette>
#include <QColor>

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
        QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Unknown);
        QPalette dark;
        const QColor window(53, 53, 53);
        const QColor base(35, 35, 35);
        const QColor text(Qt::white);
        const QColor highlight(42, 130, 218);
        const QColor disabled(128, 128, 128);
        dark.setColor(QPalette::Window,          window);
        dark.setColor(QPalette::WindowText,      text);
        dark.setColor(QPalette::Base,            base);
        dark.setColor(QPalette::AlternateBase,   window);
        dark.setColor(QPalette::ToolTipBase,     Qt::white);
        dark.setColor(QPalette::ToolTipText,     Qt::white);
        dark.setColor(QPalette::Text,            text);
        dark.setColor(QPalette::Button,          window);
        dark.setColor(QPalette::ButtonText,      text);
        dark.setColor(QPalette::BrightText,      Qt::red);
        dark.setColor(QPalette::Link,            highlight);
        dark.setColor(QPalette::Highlight,       highlight);
        dark.setColor(QPalette::HighlightedText, Qt::black);
        dark.setColor(QPalette::Disabled, QPalette::Text,       disabled);
        dark.setColor(QPalette::Disabled, QPalette::ButtonText, disabled);
        dark.setColor(QPalette::Disabled, QPalette::WindowText, disabled);
        qApp->setPalette(dark);
        config.setOption("theme", "dark");
    } else if (key == "light") {
        QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Light);
        qApp->setPalette(QPalette());
        config.setOption("theme", "light");
    } else {
        qApp->setPalette(QPalette());
        QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Unknown);
        config.setOption("theme", "system");
    }
}
