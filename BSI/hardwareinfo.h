#ifndef HARDWAREINFO_H
#define HARDWAREINFO_H

#include <QDialog>
#include <QSysInfo>
#include <QRegularExpression>
#include <QStringList>
#include <QStorageInfo>
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

namespace Ui {
class hardwareInfo;
}

class hardwareInfo : public QDialog
{
    Q_OBJECT

public:
    explicit hardwareInfo();
    ~hardwareInfo();

private:
    Ui::hardwareInfo *ui;
    QMap<QString, QString> hardwareMap;
};

#endif // HARDWAREINFO_H
