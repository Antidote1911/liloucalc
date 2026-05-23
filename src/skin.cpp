#include "skin.h"
#include "dsettings.h"
#include <QApplication>
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
    static const QPalette s_systemPalette = qApp->palette();
    DSettings config;
    if (key == "dark") {
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
        QPalette light;
        const QColor highlight(0, 120, 215);
        light.setColor(QPalette::Window,          QColor(240, 240, 240));
        light.setColor(QPalette::WindowText,      Qt::black);
        light.setColor(QPalette::Base,            Qt::white);
        light.setColor(QPalette::AlternateBase,   QColor(233, 233, 233));
        light.setColor(QPalette::ToolTipBase,     Qt::white);
        light.setColor(QPalette::ToolTipText,     Qt::black);
        light.setColor(QPalette::Text,            Qt::black);
        light.setColor(QPalette::Button,          QColor(240, 240, 240));
        light.setColor(QPalette::ButtonText,      Qt::black);
        light.setColor(QPalette::BrightText,      Qt::red);
        light.setColor(QPalette::Link,            QColor(0, 0, 255));
        light.setColor(QPalette::Highlight,       highlight);
        light.setColor(QPalette::HighlightedText, Qt::white);
        qApp->setPalette(light);
        config.setOption("theme", "light");
    } else {
        qApp->setPalette(s_systemPalette);
        config.setOption("theme", "system");
    }
}
