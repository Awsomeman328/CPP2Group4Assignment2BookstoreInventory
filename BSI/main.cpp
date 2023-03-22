#include "mainwindow.h"
#include "utilities.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    outputToLogFile("main() Starting Program, ...");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
