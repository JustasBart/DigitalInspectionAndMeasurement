#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>

namespace Ui {
class StartupDialog;
}

class StartupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartupDialog(QWidget *parent = nullptr);
    ~StartupDialog();

signals:
    void sendData(QString param);

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::StartupDialog *ui;
};

#endif // STARTUPDIALOG_H
