#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <set>
#include <deque>
#include "dbmanager.h"
#include "hashpasswordencryptor.h"
#include "backend.h"
#include "book.h"
#include "utilities.h"

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
    //QAction *newAction;
    QAction *importAction;
    QAction *exportAction;
    QAction *exitAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *notesAction;
    QAction *aboutAction;

    void showNotesDialog();
    void showAboutDialog();
    void showHardwareDialog();
    void showBookErrorDialog();

    // Define a custom comparison function that compares two Book objects based on their MSRP value
    struct CompareBookByMSRP {
        bool operator()(const Book& b1, const Book& b2) const;
    };

    // Define the multiset container (Shopping List) that holds Books and uses the custom comparison function above
    multiset<Book, CompareBookByMSRP> shoppingList;
    std::deque<Book> bookList;


public slots:
    void createDB();
    void createTable();
    void readTable();
    void searchDB();
    void logIn();
    void exitProgram();
    void addBookToDB();
    void importCSV();
    void exportCSV();
    void toggleAdminFeatures(bool isEnabled);
};
#endif // MAINWINDOW_H
