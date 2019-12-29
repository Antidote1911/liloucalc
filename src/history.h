#ifndef HISTORY_H
#define HISTORY_H

#include <QObject>
#include <QMessageBox>

class History : public QObject
{
    Q_OBJECT
public:
    explicit History(QObject *parent = nullptr);
    QString readhistory();
    bool clearhistory();
    void savehistory(QString texttowrite);

signals:

public slots:

private:

    QString historyFilePath;
    QMessageBox dialogInfos;


};

#endif // HISTORY_H
