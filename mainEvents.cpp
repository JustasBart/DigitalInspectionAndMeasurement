#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_contrastSpinBox_valueChanged(int arg1)
{
    _camObj.setParam(CAP_PROP_CONTRAST, arg1);
}

void MainWindow::on_brightnesspinBox_valueChanged(int arg1)
{
    _camObj.setParam(CAP_PROP_BRIGHTNESS, arg1);
}

void MainWindow::on_saturationSpinBox_valueChanged(int arg1)
{
    _camObj.setParam(CAP_PROP_SATURATION, arg1);
}

void MainWindow::on_focusButton_pressed()
{
    if (ui -> focusButton -> text() == "Focus: Auto")
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 0);
        ui -> focusButton -> setText("Focus: Manual");

        ui -> focusLabel -> setEnabled(true);
        ui -> focusSpinBox -> setEnabled(true);
    }
    else
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 1);
        ui -> focusButton -> setText("Focus: Auto");

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
