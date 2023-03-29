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
    QScreen *screenToSplash = QGuiApplication::primaryScreen();
    QList screens = QGuiApplication::screens();

    if(screens.size() > 1)
        screenToSplash = screens.at(1);

    QSize screenGeometry = screenToSplash->size();

    // Set the size of the splash screen to 15% of the screen. B/c scaling works linearly and not squarely,
    // we need to up the scale amount by itself. Normally this would mean to square the value,
    // but since it is a decimal that would shrink the value, so we get its square-root instead.
    splashPixmap = splashPixmap.scaled(screenGeometry * sqrt(.15), Qt::KeepAspectRatio);

    QSplashScreen splash(screenToSplash, splashPixmap, Qt::WindowStaysOnTopHint);

    splash.show();

    QTimer::singleShot(3872, &splash, SLOT(close())); // This time amount is EXTREMELY arbitrary.

    MainWindow w;
    QRect primaryGeometry = QGuiApplication::primaryScreen()->geometry();
    w.move(primaryGeometry.center() - w.rect().center());
    QTimer::singleShot(3872, &w, SLOT(show())); // This time is to match up with the time above.
    return a.exec();
}
