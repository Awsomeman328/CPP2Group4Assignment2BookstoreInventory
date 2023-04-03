#ifndef NOTESDIALOG_H
#define NOTESDIALOG_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

namespace Ui {
class NotesDialog;
}

class NotesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NotesDialog();
    ~NotesDialog();

private slots:
    void onSaveNoteClicked();

private:
    Ui::NotesDialog *ui;
    QString m_noteFilePath;
};

#endif // NOTESDIALOG_H
