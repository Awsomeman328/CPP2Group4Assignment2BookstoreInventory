/********************************************************************************
** Form generated from reading UI file 'loginscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINSCREEN_H
#define UI_LOGINSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *username;
    QLineEdit *password;
    QLabel *label_3;
    QPushButton *loginBtn;
    QCheckBox *checkBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(50, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 110, 61, 31));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(280, 110, 81, 31));
        username = new QLineEdit(Dialog);
        username->setObjectName("username");
        username->setGeometry(QRect(30, 150, 113, 22));
        password = new QLineEdit(Dialog);
        password->setObjectName("password");
        password->setGeometry(QRect(250, 150, 113, 22));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 30, 161, 51));
        loginBtn = new QPushButton(Dialog);
        loginBtn->setObjectName("loginBtn");
        loginBtn->setGeometry(QRect(150, 200, 75, 24));
        checkBox = new QCheckBox(Dialog);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(250, 200, 111, 20));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Username", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Password", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "Welcome to Scroll Rack", nullptr));
        loginBtn->setText(QCoreApplication::translate("Dialog", "Login", nullptr));
        checkBox->setText(QCoreApplication::translate("Dialog", "Remember Me", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINSCREEN_H
