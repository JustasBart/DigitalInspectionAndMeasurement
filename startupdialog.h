#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>
#include <QString>

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
    void sendData(unsigned int val, QString param);

private slots:

    void on_camPortComboBox_currentIndexChanged(const QString &arg1);
    void on_resComboBox_currentIndexChanged(const QString &arg1);
    void on_fpsComboBox_currentIndexChanged(const QString &arg1);
    void on_fullScreenCheckBox_toggled(bool checked);

private:
    Ui::StartupDialog *ui;
};

#endif // STARTUPDIALOG_H
