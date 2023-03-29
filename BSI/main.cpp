#include "mainwindow.h"
#include "utilities.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    outputToLogFile("main() Starting Program, ...");

    QApplication a(argc, argv);
    QPixmap splashPixmap("scrollRackSplash.png");
    QSplashScreen *splash= new QSplashScreen;
    splash->setPixmap(splashPixmap);
    splash->show();

    MainWindow w;
    QTimer::singleShot(2500, splash, SLOT(close()));
    QTimer::singleShot(2500, &w, SLOT(show()));
    return a.exec();
}
