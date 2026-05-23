#ifndef SKIN_H
#define SKIN_H

#include <QObject>

class Skin : public QObject
{
    Q_OBJECT

public:
    explicit Skin(QObject *parent = nullptr);

    QString getSkin(const QString &key);
    void setSkin(const QString &key);
};

#endif // SKIN_H
