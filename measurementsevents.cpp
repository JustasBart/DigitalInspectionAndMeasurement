#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

void MainWindow::on_positionCalibrationButton_clicked()
{
    if(ui->positionCalibrationButton->text() == "Position calibration")
    {
        ui->positionCalibrationButton->setText("*Calibrating*");

        _videoFPSTimer.stop();
    }
    else
    {
        ui->positionCalibrationButton->setText("Position calibration");

        _videoFPSTimer.start();
    }
}
