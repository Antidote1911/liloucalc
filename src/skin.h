#ifndef SKIN_H
#define SKIN_H

#include <QObject>
#include <Qt>

class Skin : public QObject
{
    Q_OBJECT

public:
    explicit Skin(QObject *parent = nullptr);

    QString getSkin(const QString &key);
    void setSkin(const QString &key);

private slots:
    void onColorSchemeChanged(Qt::ColorScheme scheme);

private:
    void applyDark();
    void applyLight();
    void applySystem();
};

#endif // SKIN_H
