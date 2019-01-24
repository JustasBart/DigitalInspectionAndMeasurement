#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_contrastSpinBox_valueChanged(int arg1)
{
    _camObj.setParam(CAP_PROP_CONTRAST, arg1);
}

void MainWindow::on_brightnesSpinBox_valueChanged(int arg1)
{
    _camObj.setParam(CAP_PROP_BRIGHTNESS, arg1);
}

void MainWindow::on_saturationSpinBox_valueChanged(int arg1)
{
    _camObj.setParam(CAP_PROP_SATURATION, arg1);
}

void MainWindow::on_focusButton_pressed()
{
    if (ui -> focusButton -> text() == "Focus mode: Automatic")
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 0);
        ui -> focusButton -> setText("Focus mode: Manual");

        ui -> focusLabel -> setEnabled(true);
        ui -> focusSpinBox -> setEnabled(true);
    }
    else
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 1);
        ui -> focusButton -> setText("Focus mode: Automatic");

        ui -> focusLabel -> setEnabled(false);
        ui -> focusSpinBox -> setEnabled(false);
    }
}

void MainWindow::on_focusSpinBox_valueChanged(int arg1)
{
    _camObj.setParam(CAP_PROP_FOCUS, arg1);
}

void MainWindow::on_zoomSpinBox_valueChanged(int arg1)
{
    _camObj.setParam(CAP_PROP_ZOOM, arg1 + 100);
}

void MainWindow::on_actionSet_to_defaults_triggered()
{
    QMessageBox msgBox;

    msgBox.setText("Updating the camera details");
    msgBox.setInformativeText("Would you like to update the sidebar values?");

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);

    int ret = msgBox.exec();

    switch (ret)
    {
        case QMessageBox::Yes:
        {
            defaultCamOpt();
            defaultUIVals();
            break;
        }
        case QMessageBox::No:
        {
            defaultCamOpt();
            break;
        }
        case QMessageBox::Cancel:
        {
            return;
        }
        default:
        {
            qDebug() << "Unexpected input to the set default Camera method.";
            return;
        }
    }
}

void MainWindow::defaultCamOpt()
{
    _camObj.setParam(CAP_PROP_CONTRAST, 128);
    _camObj.setParam(CAP_PROP_BRIGHTNESS, 128);
    _camObj.setParam(CAP_PROP_SATURATION, 128);
    _camObj.setParam(CAP_PROP_FOCUS, 128);
    _camObj.setParam(CAP_PROP_ZOOM, 100);
}

void MainWindow::defaultUIVals()
{
    ui->contrastSpinBox->setValue(128);
    ui->brightnesSpinBox->setValue(128);
    ui->saturationSpinBox->setValue(128);
    ui->focusSpinBox->setValue(128);
    ui->zoomSpinBox->setValue(0);
}
