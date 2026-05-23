#include "utils.h"
#include <QFile>

QString Utils::getQssContent(const QString &path)
{
    QString content;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
        return content;
    content = file.readAll();
    file.close();

    return content;
}
