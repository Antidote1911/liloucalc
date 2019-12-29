#include "history.h"
#include "dsettings.h"
#include <QFile>
#include <QTextStream>


History::History(QObject *parent) : QObject(parent)
{

}

QString History::readhistory()
{
    DSettings config;

    historyFilePath = config.configPath() + "/history.txt";
    QFile file(historyFilePath);
    QTextStream out(&file);
    QString text="";
    if (file.open(QFile::ReadOnly))
    {
        text=(file.readAll());
    }
    else {
        file.open(QFile::WriteOnly);
        out << "";
    }
    file.close();
    return text;
}

bool History::clearhistory()
{
    bool result=false;
    dialogInfos.setIcon(QMessageBox::Question);
    dialogInfos.setText("Are you sure you want to remove history ?");
    dialogInfos.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dialogInfos.setDefaultButton(QMessageBox::Yes);
    int ret = dialogInfos.exec();
    switch (ret) {
      case QMessageBox::Yes:
    {

        DSettings config;
        historyFilePath = config.configPath() + "/history.txt";
        QFile file(historyFilePath);

        if (file.open(QFile::WriteOnly)) {
            QTextStream out(&file);
            out << "";
            result=true;
        }

        break;
    }
      case QMessageBox::No:
    {
        // Cancel was clicked
        break;
    }

      default:
          // should never be reached
          break;
    }

    return result;
}

void History::savehistory(QString texttowrite)
{
    DSettings config;
    historyFilePath = config.configPath() + "/history.txt";
    QFile file(historyFilePath);

    if (file.open(QFile::WriteOnly)) {
        QTextStream out(&file);
        out << texttowrite;

    }
    file.close();
}
