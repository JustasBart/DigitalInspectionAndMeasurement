#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

void MainWindow::on_positionCalibrationButton_clicked()
{
    if(ui->positionCalibrationButton->text() == "Position calibration")
    {
        if (ui->streamingButton->text() != "Streaming")
        {
            QMessageBox msgBox;

            msgBox.setText("Calibration process");
            msgBox.setInformativeText("The calibration process cannot be done in static image mode.\nWould you like to switch back to steaming mode?");

            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);

            int ret = msgBox.exec();

            switch (ret)
            {
                case QMessageBox::Yes:
                    qDebug() << "User chose to enter live mode in order to calibrate.";
                    ui->streamingButton->click();
                    break;
                case QMessageBox::No:
                    return;
                default:
                    Errors::fatalError("Unexpected input received in 'positionCalibration'");
                    return;
            }
        }

        ui->modesGroup->setEnabled(false);
        ui->calibrationGroup->setVisible(true);
        ui->calibrationGroup->setEnabled(true);

        ui->positionCalibrationButton->setText("*Confirm calibration*");
        ui->calibrationLabel->setText("Calibrating...");

        ui->positionCalibrationButton->setStyleSheet("background-color: cyan");
        setMeasurementButtons(false);

        _calibrationInProgress = true;
    }
    else
    {
        ui->modesGroup->setEnabled(true);
        ui->calibrationGroup->setVisible(false);
        ui->calibrationGroup->setEnabled(false);

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
