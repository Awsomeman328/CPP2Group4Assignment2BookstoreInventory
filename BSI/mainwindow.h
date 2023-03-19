#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>

#include "dbmanager.h"
#include "hashpasswordencryptor.h"
#include "backend.h"

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

public slots:
    void createDB();
    void createTable();
    void readTable();
    void searchDB();
    void logIn();
    void exitProgram();
};
#endif // MAINWINDOW_H
