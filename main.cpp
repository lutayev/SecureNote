#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QIcon icon (":/Images/png/SecureNote.png");
    w.setWindowIcon(icon);
    w.show();

    return a.exec();
}
