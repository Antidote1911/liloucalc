#include "utils.h"
#include <QFile>

QString Utils::getQssContent(const QString &path)
{
    QString content;
    QFile file(path);

    file.open(QIODevice::ReadOnly);
    content = file.readAll();
    file.close();

    return content;
}
