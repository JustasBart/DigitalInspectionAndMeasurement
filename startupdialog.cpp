#include "startupdialog.h"
#include "ui_startupdialog.h"

StartupDialog::StartupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartupDialog)
{
    ui->setupUi(this);

    loadSettings();
}

StartupDialog::~StartupDialog()
{
    saveSettings();

    delete ui;
}

void StartupDialog::on_camPortComboBox_currentIndexChanged(const QString &arg1)
{
    emit sendData(0, arg1);
}

void StartupDialog::on_resComboBox_currentIndexChanged(const QString &arg1)
{
    emit sendData(1, arg1);
}

void StartupDialog::on_fpsComboBox_currentIndexChanged(const QString &arg1)
{
    emit sendData(2, arg1);
}

void StartupDialog::on_fullScreenCheckBox_toggled(bool checked)
{
    emit sendData(3, QString::number(checked));
}

void StartupDialog::on_savePreferencesCheckBox_toggled(bool checked)
{
    emit sendData(4, QString::number(checked));
}

void StartupDialog::on_buttonBox_rejected()
{
    Errors::fatalError("The user canceled the setup dialog.");
}

void StartupDialog::loadSettings()
{
    QVariant settingsVar;

    settingsVar = UserSettings::loadSettings("savePref", 0, GROUP_LOCATION);
    if (settingsVar.toBool())
    {
        ui->savePreferencesCheckBox->setCheckState( Qt::Checked );

        settingsVar = UserSettings::loadSettings("fullScreen", 0, GROUP_LOCATION);
        if (settingsVar.toBool())
        {
            ui->fullScreenCheckBox->setCheckState( Qt::Checked );
        }
        else
            ui->fullScreenCheckBox->setCheckState( Qt::Unchecked );

        settingsVar = UserSettings::loadSettings("fullScreen", 0, GROUP_LOCATION);
    }
    else
        ui->savePreferencesCheckBox->setCheckState( Qt::Unchecked );
}

void StartupDialog::saveSettings()
{
    if (ui->savePreferencesCheckBox->checkState() == Qt::Checked)
    {
        UserSettings::saveSettings("savePref", ui->savePreferencesCheckBox->checkState(), GROUP_LOCATION);
    }
}
