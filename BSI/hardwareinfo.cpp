#include "hardwareinfo.h"
#include "ui_hardwareinfo.h"
#include <QSysInfo>
#include <QRegularExpression>
#include <QStringList>
#include <QStorageInfo>

hardwareInfo::hardwareInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hardwareInfo)
{
    QSysInfo *sysInfo = new QSysInfo();
    ui->setupUi(this);

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setItem(0,0, new QTableWidgetItem("Property"));
    ui->tableWidget->setItem(0,1, new QTableWidgetItem("Value"));

    QString buildAbi = sysInfo->buildAbi();
    QRegularExpression rx("[-]");//parses buildAbi by '-'
    QStringList list = buildAbi.split(rx);

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
}

hardwareInfo::~hardwareInfo()
{
    delete ui;
}
