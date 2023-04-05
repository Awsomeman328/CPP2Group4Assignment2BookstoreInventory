/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_10;
    QLabel *labelUsername;
    QLabel *labelPassword;
    QVBoxLayout *verticalLayout_11;
    QLineEdit *lineEditUsername;
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonLogIn;
    QPushButton *pushButtonExit;
    QFrame *line_23;
    QHBoxLayout *horizontalLayout_19;
    QTabWidget *tabWidget;
    QWidget *tabMainMenu;
    QWidget *verticalLayoutWidget_7;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_20;
    QLabel *labelSearchDatabase;
    QFrame *line_24;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_21;
    QLabel *labelSearchBy;
    QComboBox *comboBoxSearchBy;
    QHBoxLayout *horizontalLayout_22;
    QLineEdit *lineEditSearchDB;
    QPushButton *btnSearchDB;
    QFrame *line_25;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_26;
    QFrame *line_26;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditISBN;
    QLineEdit *lineEditTITLE;
    QLineEdit *lineEditAUTHOR;
    QLineEdit *lineEditYEAR;
    QLineEdit *lineEditPUBLISHER;
    QLineEdit *lineEditDESC;
    QLineEdit *lineEditGENRE;
    QLineEdit *lineEditMSRP;
    QLineEdit *lineEditQUANTITY;
    QPushButton *pushButtonAddToDB;
    QFrame *line_27;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_28;
    QFrame *line_28;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_33;
    QLabel *labelAddBy;
    QComboBox *comboBoxShoppingListAddBy;
    QHBoxLayout *horizontalLayout_34;
    QLineEdit *lineEditSearchDBAddShoppingList;
    QPushButton *btnSearchDBAddShoppingList;
    QFrame *line_29;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_30;
    QFrame *line_30;
    QPushButton *pushButtonDisplayShoppingList;
    QFrame *line_31;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_32;
    QFrame *line_32;
    QPushButton *pushButtonPurchaseShoppingList;
    QWidget *tabAdminMenu;
    QWidget *verticalLayoutWidget_8;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_6;
    QFrame *line_33;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_17;
    QLabel *labelUsername_2;
    QLabel *labelPassword_2;
    QVBoxLayout *verticalLayout_18;
    QLineEdit *lineEditNewUserUsername;
    QLineEdit *lineEditNewUserPassword;
    QPushButton *pushButtonAddNewUser;
    QFrame *line_34;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_35;
    QFrame *line_35;
    QVBoxLayout *verticalLayout_19;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_20;
    QLabel *labelUsername_3;
    QLabel *labelPassword_3;
    QVBoxLayout *verticalLayout_21;
    QLineEdit *lineEditChangeUserUsername;
    QLineEdit *lineEditChangeUserPassword;
    QPushButton *pushButtonChangeUserPass;
    QFrame *line_36;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_37;
    QFrame *line_37;
    QLabel *label_38;
    QFrame *line_38;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_39;
    QFrame *line_39;
    QVBoxLayout *verticalLayout_22;
    QHBoxLayout *horizontalLayout_35;
    QLabel *labelAddBy_2;
    QComboBox *comboBoxBookListAddBy;
    QHBoxLayout *horizontalLayout_36;
    QLineEdit *lineEditSearchDBAddBookList;
    QPushButton *btnSearchDBAddBookList;
    QFrame *line_40;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_41;
    QFrame *line_41;
    QPushButton *pushButtonPrintBookList;
    QFrame *line_42;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_43;
    QFrame *line_43;
    QLabel *label_44;
    QFrame *line_44;
    QTextEdit *textEditLarge;
    QMenuBar *menubar;
    QMenu *menuPlease;
    QMenu *menuAdd;
    QMenu *menuA;
    QMenu *menuMenu;
    QMenu *menuHere;
    QMenu *menuTo;
    QMenu *menuMake;
    QMenu *menuThis;
    QMenu *menuMenu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 800);
        MainWindow->setMinimumSize(QSize(1280, 800));
        QIcon icon;
        icon.addFile(QString::fromUtf8("scrollRackSplash.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 1271, 751));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        labelUsername = new QLabel(verticalLayoutWidget);
        labelUsername->setObjectName("labelUsername");

        verticalLayout_10->addWidget(labelUsername);

        labelPassword = new QLabel(verticalLayoutWidget);
        labelPassword->setObjectName("labelPassword");

        verticalLayout_10->addWidget(labelPassword);


        horizontalLayout_10->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName("verticalLayout_11");
        lineEditUsername = new QLineEdit(verticalLayoutWidget);
        lineEditUsername->setObjectName("lineEditUsername");

        verticalLayout_11->addWidget(lineEditUsername);

        lineEditPassword = new QLineEdit(verticalLayoutWidget);
        lineEditPassword->setObjectName("lineEditPassword");

        verticalLayout_11->addWidget(lineEditPassword);


        horizontalLayout_10->addLayout(verticalLayout_11);


        verticalLayout_9->addLayout(horizontalLayout_10);

        pushButtonLogIn = new QPushButton(verticalLayoutWidget);
        pushButtonLogIn->setObjectName("pushButtonLogIn");

        verticalLayout_9->addWidget(pushButtonLogIn);


        horizontalLayout_5->addLayout(verticalLayout_9);

        pushButtonExit = new QPushButton(verticalLayoutWidget);
        pushButtonExit->setObjectName("pushButtonExit");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonExit->sizePolicy().hasHeightForWidth());
        pushButtonExit->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(pushButtonExit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        line_23 = new QFrame(verticalLayoutWidget);
        line_23->setObjectName("line_23");
        line_23->setFrameShape(QFrame::HLine);
        line_23->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_23);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        tabWidget = new QTabWidget(verticalLayoutWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMaximumSize(QSize(630, 16777215));
        tabWidget->setBaseSize(QSize(0, 0));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabMainMenu = new QWidget();
        tabMainMenu->setObjectName("tabMainMenu");
        verticalLayoutWidget_7 = new QWidget(tabMainMenu);
        verticalLayoutWidget_7->setObjectName("verticalLayoutWidget_7");
        verticalLayoutWidget_7->setGeometry(QRect(10, 10, 601, 571));
        verticalLayout_12 = new QVBoxLayout(verticalLayoutWidget_7);
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        labelSearchDatabase = new QLabel(verticalLayoutWidget_7);
        labelSearchDatabase->setObjectName("labelSearchDatabase");

        horizontalLayout_20->addWidget(labelSearchDatabase);

        line_24 = new QFrame(verticalLayoutWidget_7);
        line_24->setObjectName("line_24");
        line_24->setFrameShape(QFrame::VLine);
        line_24->setFrameShadow(QFrame::Sunken);

        horizontalLayout_20->addWidget(line_24);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName("verticalLayout_13");
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        labelSearchBy = new QLabel(verticalLayoutWidget_7);
        labelSearchBy->setObjectName("labelSearchBy");
        sizePolicy1.setHeightForWidth(labelSearchBy->sizePolicy().hasHeightForWidth());
        labelSearchBy->setSizePolicy(sizePolicy1);

        horizontalLayout_21->addWidget(labelSearchBy);

        comboBoxSearchBy = new QComboBox(verticalLayoutWidget_7);
        comboBoxSearchBy->addItem(QString());
        comboBoxSearchBy->addItem(QString());
        comboBoxSearchBy->addItem(QString());
        comboBoxSearchBy->addItem(QString());
        comboBoxSearchBy->addItem(QString());
        comboBoxSearchBy->addItem(QString());
        comboBoxSearchBy->addItem(QString());
        comboBoxSearchBy->setObjectName("comboBoxSearchBy");
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBoxSearchBy->sizePolicy().hasHeightForWidth());
        comboBoxSearchBy->setSizePolicy(sizePolicy2);

        horizontalLayout_21->addWidget(comboBoxSearchBy);


        verticalLayout_13->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName("horizontalLayout_22");
        lineEditSearchDB = new QLineEdit(verticalLayoutWidget_7);
        lineEditSearchDB->setObjectName("lineEditSearchDB");

        horizontalLayout_22->addWidget(lineEditSearchDB);

        btnSearchDB = new QPushButton(verticalLayoutWidget_7);
        btnSearchDB->setObjectName("btnSearchDB");

        horizontalLayout_22->addWidget(btnSearchDB);


        verticalLayout_13->addLayout(horizontalLayout_22);


        horizontalLayout_20->addLayout(verticalLayout_13);


        verticalLayout_12->addLayout(horizontalLayout_20);

        line_25 = new QFrame(verticalLayoutWidget_7);
        line_25->setObjectName("line_25");
        line_25->setFrameShape(QFrame::HLine);
        line_25->setFrameShadow(QFrame::Sunken);

        verticalLayout_12->addWidget(line_25);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        label_26 = new QLabel(verticalLayoutWidget_7);
        label_26->setObjectName("label_26");
        sizePolicy1.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy1);

        horizontalLayout_23->addWidget(label_26);

        line_26 = new QFrame(verticalLayoutWidget_7);
        line_26->setObjectName("line_26");
        line_26->setFrameShape(QFrame::VLine);
        line_26->setFrameShadow(QFrame::Sunken);

        horizontalLayout_23->addWidget(line_26);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lineEditISBN = new QLineEdit(verticalLayoutWidget_7);
        lineEditISBN->setObjectName("lineEditISBN");

        verticalLayout->addWidget(lineEditISBN);

        lineEditTITLE = new QLineEdit(verticalLayoutWidget_7);
        lineEditTITLE->setObjectName("lineEditTITLE");

        verticalLayout->addWidget(lineEditTITLE);

        lineEditAUTHOR = new QLineEdit(verticalLayoutWidget_7);
        lineEditAUTHOR->setObjectName("lineEditAUTHOR");

        verticalLayout->addWidget(lineEditAUTHOR);

        lineEditYEAR = new QLineEdit(verticalLayoutWidget_7);
        lineEditYEAR->setObjectName("lineEditYEAR");

        verticalLayout->addWidget(lineEditYEAR);

        lineEditPUBLISHER = new QLineEdit(verticalLayoutWidget_7);
        lineEditPUBLISHER->setObjectName("lineEditPUBLISHER");

        verticalLayout->addWidget(lineEditPUBLISHER);

        lineEditDESC = new QLineEdit(verticalLayoutWidget_7);
        lineEditDESC->setObjectName("lineEditDESC");

        verticalLayout->addWidget(lineEditDESC);

        lineEditGENRE = new QLineEdit(verticalLayoutWidget_7);
        lineEditGENRE->setObjectName("lineEditGENRE");

        verticalLayout->addWidget(lineEditGENRE);

        lineEditMSRP = new QLineEdit(verticalLayoutWidget_7);
        lineEditMSRP->setObjectName("lineEditMSRP");

        verticalLayout->addWidget(lineEditMSRP);

        lineEditQUANTITY = new QLineEdit(verticalLayoutWidget_7);
        lineEditQUANTITY->setObjectName("lineEditQUANTITY");

        verticalLayout->addWidget(lineEditQUANTITY);


        horizontalLayout_23->addLayout(verticalLayout);

        pushButtonAddToDB = new QPushButton(verticalLayoutWidget_7);
        pushButtonAddToDB->setObjectName("pushButtonAddToDB");

        horizontalLayout_23->addWidget(pushButtonAddToDB);


        verticalLayout_12->addLayout(horizontalLayout_23);

        line_27 = new QFrame(verticalLayoutWidget_7);
        line_27->setObjectName("line_27");
        line_27->setFrameShape(QFrame::HLine);
        line_27->setFrameShadow(QFrame::Sunken);

        verticalLayout_12->addWidget(line_27);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName("horizontalLayout_24");
        label_28 = new QLabel(verticalLayoutWidget_7);
        label_28->setObjectName("label_28");
        sizePolicy1.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy1);

        horizontalLayout_24->addWidget(label_28);

        line_28 = new QFrame(verticalLayoutWidget_7);
        line_28->setObjectName("line_28");
        line_28->setFrameShape(QFrame::VLine);
        line_28->setFrameShadow(QFrame::Sunken);

        horizontalLayout_24->addWidget(line_28);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName("verticalLayout_15");
        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setObjectName("horizontalLayout_33");
        labelAddBy = new QLabel(verticalLayoutWidget_7);
        labelAddBy->setObjectName("labelAddBy");
        sizePolicy1.setHeightForWidth(labelAddBy->sizePolicy().hasHeightForWidth());
        labelAddBy->setSizePolicy(sizePolicy1);

        horizontalLayout_33->addWidget(labelAddBy);

        comboBoxShoppingListAddBy = new QComboBox(verticalLayoutWidget_7);
        comboBoxShoppingListAddBy->addItem(QString());
        comboBoxShoppingListAddBy->addItem(QString());
        comboBoxShoppingListAddBy->addItem(QString());
        comboBoxShoppingListAddBy->addItem(QString());
        comboBoxShoppingListAddBy->addItem(QString());
        comboBoxShoppingListAddBy->addItem(QString());
        comboBoxShoppingListAddBy->addItem(QString());
        comboBoxShoppingListAddBy->setObjectName("comboBoxShoppingListAddBy");
        sizePolicy2.setHeightForWidth(comboBoxShoppingListAddBy->sizePolicy().hasHeightForWidth());
        comboBoxShoppingListAddBy->setSizePolicy(sizePolicy2);

        horizontalLayout_33->addWidget(comboBoxShoppingListAddBy);


        verticalLayout_15->addLayout(horizontalLayout_33);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setObjectName("horizontalLayout_34");
        lineEditSearchDBAddShoppingList = new QLineEdit(verticalLayoutWidget_7);
        lineEditSearchDBAddShoppingList->setObjectName("lineEditSearchDBAddShoppingList");

        horizontalLayout_34->addWidget(lineEditSearchDBAddShoppingList);

        btnSearchDBAddShoppingList = new QPushButton(verticalLayoutWidget_7);
        btnSearchDBAddShoppingList->setObjectName("btnSearchDBAddShoppingList");

        horizontalLayout_34->addWidget(btnSearchDBAddShoppingList);


        verticalLayout_15->addLayout(horizontalLayout_34);


        horizontalLayout_24->addLayout(verticalLayout_15);


        verticalLayout_12->addLayout(horizontalLayout_24);

        line_29 = new QFrame(verticalLayoutWidget_7);
        line_29->setObjectName("line_29");
        line_29->setFrameShape(QFrame::HLine);
        line_29->setFrameShadow(QFrame::Sunken);

        verticalLayout_12->addWidget(line_29);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName("horizontalLayout_25");
        label_30 = new QLabel(verticalLayoutWidget_7);
        label_30->setObjectName("label_30");

        horizontalLayout_25->addWidget(label_30);

        line_30 = new QFrame(verticalLayoutWidget_7);
        line_30->setObjectName("line_30");
        line_30->setFrameShape(QFrame::VLine);
        line_30->setFrameShadow(QFrame::Sunken);

        horizontalLayout_25->addWidget(line_30);

        pushButtonDisplayShoppingList = new QPushButton(verticalLayoutWidget_7);
        pushButtonDisplayShoppingList->setObjectName("pushButtonDisplayShoppingList");

        horizontalLayout_25->addWidget(pushButtonDisplayShoppingList);


        verticalLayout_12->addLayout(horizontalLayout_25);

        line_31 = new QFrame(verticalLayoutWidget_7);
        line_31->setObjectName("line_31");
        line_31->setFrameShape(QFrame::HLine);
        line_31->setFrameShadow(QFrame::Sunken);

        verticalLayout_12->addWidget(line_31);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName("horizontalLayout_26");
        label_32 = new QLabel(verticalLayoutWidget_7);
        label_32->setObjectName("label_32");

        horizontalLayout_26->addWidget(label_32);

        line_32 = new QFrame(verticalLayoutWidget_7);
        line_32->setObjectName("line_32");
        line_32->setFrameShape(QFrame::VLine);
        line_32->setFrameShadow(QFrame::Sunken);

        horizontalLayout_26->addWidget(line_32);

        pushButtonPurchaseShoppingList = new QPushButton(verticalLayoutWidget_7);
        pushButtonPurchaseShoppingList->setObjectName("pushButtonPurchaseShoppingList");

        horizontalLayout_26->addWidget(pushButtonPurchaseShoppingList);


        verticalLayout_12->addLayout(horizontalLayout_26);

        tabWidget->addTab(tabMainMenu, QString());
        tabAdminMenu = new QWidget();
        tabAdminMenu->setObjectName("tabAdminMenu");
        tabAdminMenu->setEnabled(false);
        verticalLayoutWidget_8 = new QWidget(tabAdminMenu);
        verticalLayoutWidget_8->setObjectName("verticalLayoutWidget_8");
        verticalLayoutWidget_8->setGeometry(QRect(10, 10, 601, 571));
        verticalLayout_14 = new QVBoxLayout(verticalLayoutWidget_8);
        verticalLayout_14->setObjectName("verticalLayout_14");
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName("horizontalLayout_27");
        label_6 = new QLabel(verticalLayoutWidget_8);
        label_6->setObjectName("label_6");

        horizontalLayout_27->addWidget(label_6);

        line_33 = new QFrame(verticalLayoutWidget_8);
        line_33->setObjectName("line_33");
        line_33->setFrameShape(QFrame::VLine);
        line_33->setFrameShadow(QFrame::Sunken);

        horizontalLayout_27->addWidget(line_33);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName("verticalLayout_16");
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName("verticalLayout_17");
        labelUsername_2 = new QLabel(verticalLayoutWidget_8);
        labelUsername_2->setObjectName("labelUsername_2");

        verticalLayout_17->addWidget(labelUsername_2);

        labelPassword_2 = new QLabel(verticalLayoutWidget_8);
        labelPassword_2->setObjectName("labelPassword_2");

        verticalLayout_17->addWidget(labelPassword_2);


        horizontalLayout_11->addLayout(verticalLayout_17);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName("verticalLayout_18");
        lineEditNewUserUsername = new QLineEdit(verticalLayoutWidget_8);
        lineEditNewUserUsername->setObjectName("lineEditNewUserUsername");

        verticalLayout_18->addWidget(lineEditNewUserUsername);

        lineEditNewUserPassword = new QLineEdit(verticalLayoutWidget_8);
        lineEditNewUserPassword->setObjectName("lineEditNewUserPassword");

        verticalLayout_18->addWidget(lineEditNewUserPassword);


        horizontalLayout_11->addLayout(verticalLayout_18);


        verticalLayout_16->addLayout(horizontalLayout_11);

        pushButtonAddNewUser = new QPushButton(verticalLayoutWidget_8);
        pushButtonAddNewUser->setObjectName("pushButtonAddNewUser");

        verticalLayout_16->addWidget(pushButtonAddNewUser);


        horizontalLayout_27->addLayout(verticalLayout_16);


        verticalLayout_14->addLayout(horizontalLayout_27);

        line_34 = new QFrame(verticalLayoutWidget_8);
        line_34->setObjectName("line_34");
        line_34->setFrameShape(QFrame::HLine);
        line_34->setFrameShadow(QFrame::Sunken);

        verticalLayout_14->addWidget(line_34);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName("horizontalLayout_28");
        label_35 = new QLabel(verticalLayoutWidget_8);
        label_35->setObjectName("label_35");

        horizontalLayout_28->addWidget(label_35);

        line_35 = new QFrame(verticalLayoutWidget_8);
        line_35->setObjectName("line_35");
        line_35->setFrameShape(QFrame::VLine);
        line_35->setFrameShadow(QFrame::Sunken);

        horizontalLayout_28->addWidget(line_35);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setObjectName("verticalLayout_19");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setObjectName("verticalLayout_20");
        labelUsername_3 = new QLabel(verticalLayoutWidget_8);
        labelUsername_3->setObjectName("labelUsername_3");

        verticalLayout_20->addWidget(labelUsername_3);

        labelPassword_3 = new QLabel(verticalLayoutWidget_8);
        labelPassword_3->setObjectName("labelPassword_3");

        verticalLayout_20->addWidget(labelPassword_3);


        horizontalLayout_12->addLayout(verticalLayout_20);

        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setObjectName("verticalLayout_21");
        lineEditChangeUserUsername = new QLineEdit(verticalLayoutWidget_8);
        lineEditChangeUserUsername->setObjectName("lineEditChangeUserUsername");

        verticalLayout_21->addWidget(lineEditChangeUserUsername);

        lineEditChangeUserPassword = new QLineEdit(verticalLayoutWidget_8);
        lineEditChangeUserPassword->setObjectName("lineEditChangeUserPassword");

        verticalLayout_21->addWidget(lineEditChangeUserPassword);


        horizontalLayout_12->addLayout(verticalLayout_21);


        verticalLayout_19->addLayout(horizontalLayout_12);

        pushButtonChangeUserPass = new QPushButton(verticalLayoutWidget_8);
        pushButtonChangeUserPass->setObjectName("pushButtonChangeUserPass");

        verticalLayout_19->addWidget(pushButtonChangeUserPass);


        horizontalLayout_28->addLayout(verticalLayout_19);


        verticalLayout_14->addLayout(horizontalLayout_28);

        line_36 = new QFrame(verticalLayoutWidget_8);
        line_36->setObjectName("line_36");
        line_36->setFrameShape(QFrame::HLine);
        line_36->setFrameShadow(QFrame::Sunken);

        verticalLayout_14->addWidget(line_36);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName("horizontalLayout_29");
        label_37 = new QLabel(verticalLayoutWidget_8);
        label_37->setObjectName("label_37");

        horizontalLayout_29->addWidget(label_37);

        line_37 = new QFrame(verticalLayoutWidget_8);
        line_37->setObjectName("line_37");
        line_37->setFrameShape(QFrame::VLine);
        line_37->setFrameShadow(QFrame::Sunken);

        horizontalLayout_29->addWidget(line_37);

        label_38 = new QLabel(verticalLayoutWidget_8);
        label_38->setObjectName("label_38");

        horizontalLayout_29->addWidget(label_38);


        verticalLayout_14->addLayout(horizontalLayout_29);

        line_38 = new QFrame(verticalLayoutWidget_8);
        line_38->setObjectName("line_38");
        line_38->setFrameShape(QFrame::HLine);
        line_38->setFrameShadow(QFrame::Sunken);

        verticalLayout_14->addWidget(line_38);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName("horizontalLayout_30");
        label_39 = new QLabel(verticalLayoutWidget_8);
        label_39->setObjectName("label_39");

        horizontalLayout_30->addWidget(label_39);

        line_39 = new QFrame(verticalLayoutWidget_8);
        line_39->setObjectName("line_39");
        line_39->setFrameShape(QFrame::VLine);
        line_39->setFrameShadow(QFrame::Sunken);

        horizontalLayout_30->addWidget(line_39);

        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setObjectName("verticalLayout_22");
        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName("horizontalLayout_35");
        labelAddBy_2 = new QLabel(verticalLayoutWidget_8);
        labelAddBy_2->setObjectName("labelAddBy_2");
        sizePolicy1.setHeightForWidth(labelAddBy_2->sizePolicy().hasHeightForWidth());
        labelAddBy_2->setSizePolicy(sizePolicy1);

        horizontalLayout_35->addWidget(labelAddBy_2);

        comboBoxBookListAddBy = new QComboBox(verticalLayoutWidget_8);
        comboBoxBookListAddBy->addItem(QString());
        comboBoxBookListAddBy->addItem(QString());
        comboBoxBookListAddBy->addItem(QString());
        comboBoxBookListAddBy->addItem(QString());
        comboBoxBookListAddBy->addItem(QString());
        comboBoxBookListAddBy->addItem(QString());
        comboBoxBookListAddBy->addItem(QString());
        comboBoxBookListAddBy->setObjectName("comboBoxBookListAddBy");
        sizePolicy2.setHeightForWidth(comboBoxBookListAddBy->sizePolicy().hasHeightForWidth());
        comboBoxBookListAddBy->setSizePolicy(sizePolicy2);

        horizontalLayout_35->addWidget(comboBoxBookListAddBy);


        verticalLayout_22->addLayout(horizontalLayout_35);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName("horizontalLayout_36");
        lineEditSearchDBAddBookList = new QLineEdit(verticalLayoutWidget_8);
        lineEditSearchDBAddBookList->setObjectName("lineEditSearchDBAddBookList");

        horizontalLayout_36->addWidget(lineEditSearchDBAddBookList);

        btnSearchDBAddBookList = new QPushButton(verticalLayoutWidget_8);
        btnSearchDBAddBookList->setObjectName("btnSearchDBAddBookList");

        horizontalLayout_36->addWidget(btnSearchDBAddBookList);


        verticalLayout_22->addLayout(horizontalLayout_36);


        horizontalLayout_30->addLayout(verticalLayout_22);


        verticalLayout_14->addLayout(horizontalLayout_30);

        line_40 = new QFrame(verticalLayoutWidget_8);
        line_40->setObjectName("line_40");
        line_40->setFrameShape(QFrame::HLine);
        line_40->setFrameShadow(QFrame::Sunken);

        verticalLayout_14->addWidget(line_40);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setObjectName("horizontalLayout_31");
        label_41 = new QLabel(verticalLayoutWidget_8);
        label_41->setObjectName("label_41");

        horizontalLayout_31->addWidget(label_41);

        line_41 = new QFrame(verticalLayoutWidget_8);
        line_41->setObjectName("line_41");
        line_41->setFrameShape(QFrame::VLine);
        line_41->setFrameShadow(QFrame::Sunken);

        horizontalLayout_31->addWidget(line_41);

        pushButtonPrintBookList = new QPushButton(verticalLayoutWidget_8);
        pushButtonPrintBookList->setObjectName("pushButtonPrintBookList");

        horizontalLayout_31->addWidget(pushButtonPrintBookList);


        verticalLayout_14->addLayout(horizontalLayout_31);

        line_42 = new QFrame(verticalLayoutWidget_8);
        line_42->setObjectName("line_42");
        line_42->setFrameShape(QFrame::HLine);
        line_42->setFrameShadow(QFrame::Sunken);

        verticalLayout_14->addWidget(line_42);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setObjectName("horizontalLayout_32");
        label_43 = new QLabel(verticalLayoutWidget_8);
        label_43->setObjectName("label_43");

        horizontalLayout_32->addWidget(label_43);

        line_43 = new QFrame(verticalLayoutWidget_8);
        line_43->setObjectName("line_43");
        line_43->setFrameShape(QFrame::VLine);
        line_43->setFrameShadow(QFrame::Sunken);

        horizontalLayout_32->addWidget(line_43);

        label_44 = new QLabel(verticalLayoutWidget_8);
        label_44->setObjectName("label_44");

        horizontalLayout_32->addWidget(label_44);


        verticalLayout_14->addLayout(horizontalLayout_32);

        tabWidget->addTab(tabAdminMenu, QString());

        horizontalLayout_19->addWidget(tabWidget);

        line_44 = new QFrame(verticalLayoutWidget);
        line_44->setObjectName("line_44");
        line_44->setFrameShape(QFrame::VLine);
        line_44->setFrameShadow(QFrame::Sunken);

        horizontalLayout_19->addWidget(line_44);

        textEditLarge = new QTextEdit(verticalLayoutWidget);
        textEditLarge->setObjectName("textEditLarge");
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(textEditLarge->sizePolicy().hasHeightForWidth());
        textEditLarge->setSizePolicy(sizePolicy3);
        textEditLarge->setMinimumSize(QSize(600, 0));

        horizontalLayout_19->addWidget(textEditLarge);


        verticalLayout_2->addLayout(horizontalLayout_19);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 21));
        menuPlease = new QMenu(menubar);
        menuPlease->setObjectName("menuPlease");
        menuAdd = new QMenu(menubar);
        menuAdd->setObjectName("menuAdd");
        menuA = new QMenu(menubar);
        menuA->setObjectName("menuA");
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName("menuMenu");
        menuHere = new QMenu(menubar);
        menuHere->setObjectName("menuHere");
        menuTo = new QMenu(menubar);
        menuTo->setObjectName("menuTo");
        menuMake = new QMenu(menubar);
        menuMake->setObjectName("menuMake");
        menuThis = new QMenu(menubar);
        menuThis->setObjectName("menuThis");
        menuMenu_2 = new QMenu(menubar);
        menuMenu_2->setObjectName("menuMenu_2");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuPlease->menuAction());
        menubar->addAction(menuAdd->menuAction());
        menubar->addAction(menuA->menuAction());
        menubar->addAction(menuMenu->menuAction());
        menubar->addAction(menuHere->menuAction());
        menubar->addAction(menuTo->menuAction());
        menubar->addAction(menuMake->menuAction());
        menubar->addAction(menuThis->menuAction());
        menubar->addAction(menuMenu_2->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(btnSearchDB, SIGNAL(clicked()), MainWindow, SLOT(searchDB()));
        QObject::connect(pushButtonExit, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));
        QObject::connect(pushButtonLogIn, SIGNAL(clicked()), MainWindow, SLOT(logIn()));
        QObject::connect(pushButtonAddToDB, SIGNAL(clicked()), MainWindow, SLOT(addBookToDB()));
        QObject::connect(btnSearchDBAddShoppingList, SIGNAL(clicked()), MainWindow, SLOT(searchBookToShoppingList()));
        QObject::connect(btnSearchDBAddBookList, SIGNAL(clicked()), MainWindow, SLOT(searchBookToBookList()));
        QObject::connect(pushButtonDisplayShoppingList, SIGNAL(clicked()), MainWindow, SLOT(displayShoppingList()));
        QObject::connect(pushButtonPurchaseShoppingList, SIGNAL(clicked()), MainWindow, SLOT(purchaseShoppingList()));
        QObject::connect(pushButtonPrintBookList, SIGNAL(clicked()), MainWindow, SLOT(displayBookList()));
        QObject::connect(pushButtonAddNewUser, SIGNAL(clicked()), MainWindow, SLOT(addNewUser()));
        QObject::connect(pushButtonChangeUserPass, SIGNAL(clicked()), MainWindow, SLOT(changeUsersPassword()));

        tabWidget->setCurrentIndex(0);
        comboBoxSearchBy->setCurrentIndex(1);
        comboBoxShoppingListAddBy->setCurrentIndex(0);
        comboBoxBookListAddBy->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Scroll Rack - A Bookstore Inventory Database", nullptr));
        labelUsername->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        labelPassword->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        lineEditPassword->setPlaceholderText(QString());
        pushButtonLogIn->setText(QCoreApplication::translate("MainWindow", "Log In (Not Yet Implemented)", nullptr));
        pushButtonExit->setText(QCoreApplication::translate("MainWindow", "Exit Program", nullptr));
        labelSearchDatabase->setText(QCoreApplication::translate("MainWindow", "Search the Database", nullptr));
        labelSearchBy->setText(QCoreApplication::translate("MainWindow", "Search By: ", nullptr));
        comboBoxSearchBy->setItemText(0, QCoreApplication::translate("MainWindow", "ISBN", nullptr));
        comboBoxSearchBy->setItemText(1, QCoreApplication::translate("MainWindow", "Title", nullptr));
        comboBoxSearchBy->setItemText(2, QCoreApplication::translate("MainWindow", "Author", nullptr));
        comboBoxSearchBy->setItemText(3, QCoreApplication::translate("MainWindow", "Publication Year", nullptr));
        comboBoxSearchBy->setItemText(4, QCoreApplication::translate("MainWindow", "Publisher", nullptr));
        comboBoxSearchBy->setItemText(5, QCoreApplication::translate("MainWindow", "MSRP", nullptr));
        comboBoxSearchBy->setItemText(6, QCoreApplication::translate("MainWindow", "Quantity On Hand", nullptr));

        btnSearchDB->setText(QCoreApplication::translate("MainWindow", "Search Database", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Add a book to the Inventory", nullptr));
        lineEditISBN->setText(QString());
        lineEditISBN->setPlaceholderText(QCoreApplication::translate("MainWindow", "ISBN", nullptr));
        lineEditTITLE->setText(QString());
        lineEditTITLE->setPlaceholderText(QCoreApplication::translate("MainWindow", "TITLE", nullptr));
        lineEditAUTHOR->setText(QString());
        lineEditAUTHOR->setPlaceholderText(QCoreApplication::translate("MainWindow", "AUTHOR", nullptr));
        lineEditYEAR->setText(QString());
        lineEditYEAR->setPlaceholderText(QCoreApplication::translate("MainWindow", "PUBLICATION YEAR", nullptr));
        lineEditPUBLISHER->setText(QString());
        lineEditPUBLISHER->setPlaceholderText(QCoreApplication::translate("MainWindow", "PUBLISHER", nullptr));
        lineEditDESC->setText(QString());
        lineEditDESC->setPlaceholderText(QCoreApplication::translate("MainWindow", "DESCRIPTION", nullptr));
        lineEditGENRE->setText(QString());
        lineEditGENRE->setPlaceholderText(QCoreApplication::translate("MainWindow", "GENRE", nullptr));
        lineEditMSRP->setText(QString());
        lineEditMSRP->setPlaceholderText(QCoreApplication::translate("MainWindow", "MSRP", nullptr));
        lineEditQUANTITY->setText(QString());
        lineEditQUANTITY->setPlaceholderText(QCoreApplication::translate("MainWindow", "QUANTITY", nullptr));
        pushButtonAddToDB->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "Add a book to your Shopping List from the database", nullptr));
        labelAddBy->setText(QCoreApplication::translate("MainWindow", "Add By: ", nullptr));
        comboBoxShoppingListAddBy->setItemText(0, QCoreApplication::translate("MainWindow", "ISBN", nullptr));
        comboBoxShoppingListAddBy->setItemText(1, QCoreApplication::translate("MainWindow", "Title", nullptr));
        comboBoxShoppingListAddBy->setItemText(2, QCoreApplication::translate("MainWindow", "Author", nullptr));
        comboBoxShoppingListAddBy->setItemText(3, QCoreApplication::translate("MainWindow", "Publication Year", nullptr));
        comboBoxShoppingListAddBy->setItemText(4, QCoreApplication::translate("MainWindow", "Publisher", nullptr));
        comboBoxShoppingListAddBy->setItemText(5, QCoreApplication::translate("MainWindow", "MSRP", nullptr));
        comboBoxShoppingListAddBy->setItemText(6, QCoreApplication::translate("MainWindow", "Quantity On Hand", nullptr));

        btnSearchDBAddShoppingList->setText(QCoreApplication::translate("MainWindow", "Search Database And Add", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "Display your Shopping List to the screen", nullptr));
        pushButtonDisplayShoppingList->setText(QCoreApplication::translate("MainWindow", "Display Shopping List (Not Yet Implemented)", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "Purchase Items in Shopping List", nullptr));
        pushButtonPurchaseShoppingList->setText(QCoreApplication::translate("MainWindow", "Purchase Shopping List (Not Yet Implemented)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabMainMenu), QCoreApplication::translate("MainWindow", "Main Menu", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Add a new User", nullptr));
        labelUsername_2->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        labelPassword_2->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        lineEditNewUserPassword->setPlaceholderText(QString());
        pushButtonAddNewUser->setText(QCoreApplication::translate("MainWindow", "Add New User (Not Yet Implemented)", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "Change a User's Password", nullptr));
        labelUsername_3->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        labelPassword_3->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        lineEditChangeUserPassword->setPlaceholderText(QString());
        pushButtonChangeUserPass->setText(QCoreApplication::translate("MainWindow", "Change User's Password (Not Yet Implemented)", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "Import a .CSV file into the database", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "Not Yet Implemented", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "Add a book to your Book List from the inventory", nullptr));
        labelAddBy_2->setText(QCoreApplication::translate("MainWindow", "Add By: ", nullptr));
        comboBoxBookListAddBy->setItemText(0, QCoreApplication::translate("MainWindow", "ISBN", nullptr));
        comboBoxBookListAddBy->setItemText(1, QCoreApplication::translate("MainWindow", "Title", nullptr));
        comboBoxBookListAddBy->setItemText(2, QCoreApplication::translate("MainWindow", "Author", nullptr));
        comboBoxBookListAddBy->setItemText(3, QCoreApplication::translate("MainWindow", "Publication Year", nullptr));
        comboBoxBookListAddBy->setItemText(4, QCoreApplication::translate("MainWindow", "Publisher", nullptr));
        comboBoxBookListAddBy->setItemText(5, QCoreApplication::translate("MainWindow", "MSRP", nullptr));
        comboBoxBookListAddBy->setItemText(6, QCoreApplication::translate("MainWindow", "Quantity On Hand", nullptr));

        btnSearchDBAddBookList->setText(QCoreApplication::translate("MainWindow", "Search Database And Add", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "Print your Book List to the screen", nullptr));
        pushButtonPrintBookList->setText(QCoreApplication::translate("MainWindow", "Print Book List (Not Yet Implemented)", nullptr));
        label_43->setText(QCoreApplication::translate("MainWindow", "Export your Book List to a .CSV file", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "Not Yet Implemented", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAdminMenu), QCoreApplication::translate("MainWindow", "Admin Menu", nullptr));
        menuPlease->setTitle(QCoreApplication::translate("MainWindow", "Please", nullptr));
        menuAdd->setTitle(QCoreApplication::translate("MainWindow", "Use", nullptr));
        menuA->setTitle(QCoreApplication::translate("MainWindow", "The", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "UI", nullptr));
        menuHere->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuTo->setTitle(QCoreApplication::translate("MainWindow", "To", nullptr));
        menuMake->setTitle(QCoreApplication::translate("MainWindow", "Make", nullptr));
        menuThis->setTitle(QCoreApplication::translate("MainWindow", "This", nullptr));
        menuMenu_2->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
