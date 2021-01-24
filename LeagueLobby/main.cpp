#include "mainwindow.h"

#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setBold(true);
    font.setPixelSize(15);
    a.setFont(font);

    MainWindow w;
    w.show();

    return a.exec();
}
