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

void StartupDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    emit sendData("const QString text");
}
