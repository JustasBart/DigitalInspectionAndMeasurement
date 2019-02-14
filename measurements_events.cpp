#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

void MainWindow::on_positionCalibrationButton_pressed()
{
    if(ui->positionCalibrationButton->text() == "Position calibration")
    {
        ui->modesGroup->setEnabled(false);
        _videoFPSTimer.start();

        ui->positionCalibrationButton->setText("*Confirm calibration*");
        ui->calibrationLabel->setText("Calibrating...");

        ui->positionCalibrationButton->setStyleSheet("background-color: cyan");
        setMeasurementButtons(false);

        _calibrationInProgress = true;
    }
    else
    {
        ui->modesGroup->setEnabled(true);
        _videoFPSTimer.stop();

        ui->positionCalibrationButton->setText("Position calibration");
        ui->positionCalibrationButton->setStyleSheet("background-color: lightGray");

        ui->calibrationLabel->setText(">Calibrated<");
        setMeasurementButtons(true);

        _calibrationInProgress = false;
    }
}

void MainWindow::setMeasurementButtons(bool val)
{
    ui->measureButton->setEnabled(val);
    ui->detailMergeButton->setEnabled(val);
    ui->stackImagesButton->setEnabled(val);
    ui->edgeDetectButton->setEnabled(val);
}
