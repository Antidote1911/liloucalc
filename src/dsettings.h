#ifndef SETTINGS_H
#define SETTTINGS_H

#include <QObject>
#include <QSettings>

class DSettings : public QObject
{
    Q_OBJECT

public:
    DSettings(QObject *parent = 0);

    QSettings *settings;
    QString configPath();
    QString getOption(const QString &key);
    void setOption(const QString &key, const QString &value);
};

#endif // SETTINGS_H
