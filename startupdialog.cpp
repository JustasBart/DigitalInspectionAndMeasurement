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
    delete ui;
}

void StartupDialog::on_buttonBox_rejected()
{
    Errors::fatalError("The user canceled the setup dialog.");
}

void StartupDialog::loadSettings()
{
    QVariant settingsVar;

    settingsVar = UserSettings::loadSettings("saveSetupPref", 0, GROUP_LOCATION);

    if (settingsVar.toBool())
    {
        ui->saveSetupSettingsCheckBox->setCheckState( Qt::Checked );
        settingsVar = UserSettings::loadSettings("saveMainPref", 0, GROUP_LOCATION);

        if (settingsVar.toBool())
            ui->saveMainSettingsCheckBox->setCheckState( Qt::Checked );
        else
            ui->saveMainSettingsCheckBox->setCheckState( Qt::Unchecked );

        settingsVar = UserSettings::loadSettings("fullScreen", 0, GROUP_LOCATION);
        if (settingsVar.toBool())
            ui->fullScreenCheckBox->setCheckState( Qt::Checked );
        else
            ui->fullScreenCheckBox->setCheckState( Qt::Unchecked );

        settingsVar = UserSettings::loadSettings("cameraPort", 0, GROUP_LOCATION);
        if (settingsVar.toInt() != 0)
            ui->camPortComboBox->setCurrentIndex(settingsVar.toInt());
        settingsVar = UserSettings::loadSettings("resolutionSel", 0, GROUP_LOCATION);
        if (settingsVar.toInt() != 0)
            ui->resComboBox->setCurrentIndex( settingsVar.toInt() );
        settingsVar = UserSettings::loadSettings("resolutionSel", 0, GROUP_LOCATION);
        if (settingsVar.toInt() != 0)
            ui->fpsComboBox->setCurrentIndex( settingsVar.toInt() );
    }
    else
        ui->saveSetupSettingsCheckBox->setCheckState( Qt::Unchecked );
}

void StartupDialog::saveSettings()
{
    UserSettings::saveSettings("saveSetupPref", ui->saveSetupSettingsCheckBox->checkState(), GROUP_LOCATION);

    if (ui->saveSetupSettingsCheckBox->checkState() == Qt::Checked)
    {
        UserSettings::saveSettings("saveMainPref", ui->saveMainSettingsCheckBox->checkState(), GROUP_LOCATION);
        UserSettings::saveSettings("fullScreen", ui->fullScreenCheckBox->checkState(), GROUP_LOCATION);
        UserSettings::saveSettings("cameraPort", ui->camPortComboBox->currentIndex(), GROUP_LOCATION);
        UserSettings::saveSettings("resolutionSel", ui->resComboBox->currentIndex(), GROUP_LOCATION);
    }
}

void StartupDialog::flushSettings()
{
    emit sendData(0, QString::number(ui->camPortComboBox->currentIndex()));
    emit sendData(1, QString::number(ui->resComboBox->currentIndex()));
    emit sendData(2, ui->fpsComboBox->currentText());
    if (ui->fullScreenCheckBox->checkState() == Qt::Checked)
        emit sendData(3, "1");
    else
        emit sendData(3, "0");
    if (ui->saveMainSettingsCheckBox->checkState() == Qt::Checked)
        emit sendData(4, "1");
    else
        emit sendData(4, "0");
}

void StartupDialog::on_StartupDialog_finished(int result)
{
    flushSettings();
    saveSettings();
}
