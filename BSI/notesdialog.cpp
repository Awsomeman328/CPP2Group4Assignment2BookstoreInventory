#include "notesdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

NotesDialog::NotesDialog() :
    QDialog()
{
    /*
    // Set up the dialog layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QTextEdit *textEdit = new QTextEdit(this);
    QPushButton *saveButton = new QPushButton("Save", this);

    layout->addWidget(textEdit);
    layout->addWidget(saveButton);

    // Connect the save button to the onSaveNoteClicked function
    connect(saveButton, &QPushButton::clicked, this, &NotesDialog::onSaveNoteClicked);
    */

    // Create the dialog layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    // Create the text editor
    QPlainTextEdit* textEdit = new QPlainTextEdit();
    mainLayout->addWidget(textEdit);

    // Create the save button
    QPushButton* saveButton = new QPushButton(tr("Save"));
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(saveButton);
    mainLayout->addLayout(buttonLayout);

    // Load the note from the file
    QFile file("notes.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString note = in.readAll();
        textEdit->setPlainText(note);
        file.close();
    }

    // Connect the save button to the onSaveNoteClicked() slot
    connect(saveButton, &QPushButton::clicked, this, &NotesDialog::onSaveNoteClicked);
}

NotesDialog::~NotesDialog()
{
    //delete ui;
}

void NotesDialog::onSaveNoteClicked()
{
    QString note = ((QPlainTextEdit*)this->layout()->itemAt(0)->widget())->toPlainText();

    // Save the note to "notes.txt"
    QFile file("notes.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << note;
        file.close();
    }
}
