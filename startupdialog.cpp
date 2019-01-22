#include "startupdialog.h"
#include "ui_startupdialog.h"

StartupDialog::StartupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartupDialog)
{
    ui->setupUi(this);
}

StartupDialog::~StartupDialog()
{
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
