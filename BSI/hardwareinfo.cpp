#include "hardwareinfo.h"
#include "ui_hardwareinfo.h"
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QHeaderView>

hardwareInfo::hardwareInfo() :
    QDialog(),
    ui(new Ui::hardwareInfo)
{
    QSysInfo *sysInfo = new QSysInfo();

    //ui->setupUi(this);
/*
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setItem(0,0, new QTableWidgetItem("Property"));
    ui->tableWidget->setItem(0,1, new QTableWidgetItem("Value"));
*/

    // Set up the layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Add the title label
    QLabel *titleLabel = new QLabel("<h2>Hardware Information</h2>", this);
    mainLayout->addWidget(titleLabel);

    // Add the table widget
    QTableWidget *tableWidget = new QTableWidget(this);
    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalHeader()->hide();
    tableWidget->setRowCount(6);
    tableWidget->setColumnCount(2);
    tableWidget->setItem(0, 0, new QTableWidgetItem("Property"));
    tableWidget->setItem(0, 1, new QTableWidgetItem("Value"));
    tableWidget->setItem(1, 0, new QTableWidgetItem("Host Name"));
    tableWidget->setItem(1, 1, new QTableWidgetItem(sysInfo->machineHostName()));
    tableWidget->setItem(2, 0, new QTableWidgetItem("Endianness"));

    // Get build info
    QString buildAbi = sysInfo->buildAbi();
    QRegularExpression rx("[-]");//parses buildAbi by '-'
    QStringList list = buildAbi.split(rx);

    // Finish setting up the table widget and layout
    tableWidget->setItem(2, 1, new QTableWidgetItem(list[1]));
    tableWidget->setItem(3, 0, new QTableWidgetItem("Product Version"));
    tableWidget->setItem(3, 1, new QTableWidgetItem(sysInfo->prettyProductName()));
    tableWidget->setItem(4, 0, new QTableWidgetItem("Product Type"));
    tableWidget->setItem(4, 1, new QTableWidgetItem(sysInfo->productType()));
    tableWidget->setItem(5, 0, new QTableWidgetItem("Kernel Type"));
    tableWidget->setItem(5, 1, new QTableWidgetItem(sysInfo->kernelType()));
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(tableWidget);
/*
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setItem(1,0, new QTableWidgetItem("Host Name"));
    ui->tableWidget->setItem(1,1, new QTableWidgetItem(sysInfo->machineHostName()));

    ui->tableWidget->setItem(2,0, new QTableWidgetItem("Endianness"));
    ui->tableWidget->setItem(2,1, new QTableWidgetItem(list[1]));

    ui->tableWidget->setItem(3,0, new QTableWidgetItem("Product Version"));
    ui->tableWidget->setItem(3,1, new QTableWidgetItem(sysInfo->prettyProductName()));

    ui->tableWidget->setItem(4,0, new QTableWidgetItem("Product Type"));
    ui->tableWidget->setItem(4,1, new QTableWidgetItem(sysInfo->productType()));

    ui->tableWidget->setItem(5,0, new QTableWidgetItem("Kernel Type"));
    ui->tableWidget->setItem(5,1, new QTableWidgetItem(sysInfo->kernelType()));

    ui->tableWidget->setItem(6,0, new QTableWidgetItem("Architecture"));
    ui->tableWidget->setItem(6,1, new QTableWidgetItem(list[0]));
*/
/*
    setText("<h2>Hardware Information</h2>"
                "<table>"
                "<tr><td>Host Name</td><td>" + sysInfo->machineHostName() + "</td></tr>"
                "<tr><td>Endianness</td><td>" + list[1] + "</td></tr>"
                "<tr><td>Product Version</td><td>" + sysInfo->prettyProductName() + "</td></tr>"
                "<tr><td>Product Type</td><td>" + sysInfo->productType() + "</td></tr>"
                "<tr><td>Kernel Type</td><td>" + sysInfo->kernelType() + "</td></tr>"
                "<tr><td>Architecture</td><td>" + list[0] + "</td></tr>");
*/
/*
    //available amount and total amount of drive memory
    QList<QStorageInfo> storageInfoList2 = QStorageInfo::mountedVolumes();
        int rowIndex = 7;
        for (const QStorageInfo& storageInfo : storageInfoList2) {
            if (storageInfo.isValid() && storageInfo.isReady()) {
                ui->tableWidget->setItem(7,0, new QTableWidgetItem(storageInfo.rootPath()));
                ui->tableWidget->setItem(7, 1, new QTableWidgetItem(QString::number(storageInfo.bytesTotal() / (1024 * 1024)) + " MB total / " + QString::number(storageInfo.bytesAvailable() / (1024 * 1024)) + " MB available"));
                ++rowIndex;
            }
        }
*/

    //using a map to store hardware info for easy front-end access to QStrings
    QMap<QString, QString> hardwareMap;

    hardwareMap.insert("Host Name", sysInfo->machineHostName());
    hardwareMap.insert("Endianness", list[1]);
    hardwareMap.insert("Product Version", sysInfo->prettyProductName());
    hardwareMap.insert("Product Type", sysInfo->productType());
    hardwareMap.insert("Kernel Type", sysInfo->kernelType());
    hardwareMap.insert("Architecture", list[0]);

    // Store drive information in the map
    QList<QStorageInfo> storageInfoList = QStorageInfo::mountedVolumes();
    for (const QStorageInfo& storageInfo : storageInfoList) {
        if (storageInfo.isValid() && storageInfo.isReady()) {
            QString driveInfo = QString::number(storageInfo.bytesAvailable() / (1024 * 1024)) + " MB / " + QString::number(storageInfo.bytesTotal() / (1024 * 1024)) + " MB";
            hardwareMap.insert(storageInfo.rootPath(), driveInfo);
        }
    }

    //setText(text() + "</table>");

    // Add the close button
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    QPushButton *closeButton = new QPushButton("Close", this);
    connect(closeButton, &QPushButton::clicked, this, &hardwareInfo::accept);
    buttonLayout->addWidget(closeButton);
    mainLayout->addLayout(buttonLayout);
}

hardwareInfo::~hardwareInfo()
{
    delete ui;
}
