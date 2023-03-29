#include "mainwindow.h"
#include "utilities.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QScreen>

int main(int argc, char *argv[])
{
    outputToLogFile("main() Starting Program, ...");

    QApplication a(argc, argv);
    QPixmap splashPixmap("scrollRackSplash.png");
    QScreen *screen = QGuiApplication::primaryScreen();
    QList screens = QGuiApplication::screens();

    if(screens.size() > 1)
        screen = screens.at(1);


    QSplashScreen splash(screen, splashPixmap);

//    QSplashScreen *splash= new QSplashScreen;
//    splash->setPixmap(splashPixmap);
    splash.show();

    MainWindow w;
    QTimer::singleShot(2500, &splash, SLOT(close()));
    QTimer::singleShot(2500, &w, SLOT(show()));
    return a.exec();
}
