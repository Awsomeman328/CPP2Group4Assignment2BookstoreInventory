#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>

#include "dbmanager.h"
#include "hashpasswordencryptor.h"
#include "backend.h"
#include "book.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
        QMenuBar *menuBar;
        QMenu *fileMenu;
        QMenu *editMenu;
        QMenu *helpMenu;
        QAction *newAction;
        QAction *openAction;
        QAction *saveAction;
        QAction *exitAction;
        QAction *cutAction;
        QAction *copyAction;
        QAction *pasteAction;
        QAction *aboutAction;
        QAction *displayHardwareAction;

        void showAboutDialog();
        void showHardwareDialog();
        void showBookErrorDialog();

public slots:
    void createDB();
    void createTable();
    void readTable();
    void searchDB();
    void logIn();
    void exitProgram();
    void addBookToDB();
};
#endif // MAINWINDOW_H
