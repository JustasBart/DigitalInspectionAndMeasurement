#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#define GROUP_LOCATION  "GUISettings"

// QtIncludes //
#include <QDialog>
#include <QString>

// Local includes //
#include "usersettings.h"
#include "errors.h"

namespace Ui
{
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
    void on_buttonBox_rejected();
    void on_StartupDialog_finished(int result);
    void on_buttonBox_accepted();
    void on_StartupDialog_rejected();

private:
    Ui::StartupDialog *ui;

    void loadSettings();
    void saveSettings();
    void flushSettings();
};

#endif // STARTUPDIALOG_H
