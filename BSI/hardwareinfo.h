#ifndef HARDWAREINFO_H
#define HARDWAREINFO_H

#include <QMainWindow>

namespace Ui {
class hardwareInfo;
}

class hardwareInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit hardwareInfo(QWidget *parent = nullptr);
    ~hardwareInfo();

private:
    Ui::hardwareInfo *ui;
};

#endif // HARDWAREINFO_H
