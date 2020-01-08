#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Team1911");
    a.setApplicationName("LilouCalc");
    a.setApplicationVersion("1.0");
    a.setWindowIcon(QIcon(":/image/icon.svg"));
    a.setStyle("Fusion");
    MainWindow c;
    c.show();

    return a.exec();
}
