#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
        paths.append(".");
        paths.append("imageformats");
        paths.append("platforms");
        paths.append("sqldrivers");

    QApplication app(argc, argv);
    app.setLibraryPaths(paths);

    MainWindow w;
    QIcon icon (":/Images/png/SecureNote.png");
    w.setWindowIcon(icon);
    w.show();

    return app.exec();
}
