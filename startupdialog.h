#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#define GROUP_LOCATION  "PreStartOptions"

#include <QDialog>
#include <QString>
#include <errors.h>
#include "usersettings.h"

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
    void on_buttonBox_rejected();
    void on_StartupDialog_finished(int result);
    void on_savePreferencesCheckBox_toggled(bool checked);

private:
    void loadSettings();
    void saveSettings();
    Ui::StartupDialog *ui;
};

#endif // STARTUPDIALOG_H
