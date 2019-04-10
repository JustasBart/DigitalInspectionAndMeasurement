#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_focusButton_pressed()
{
    if (ui -> focusButton -> text() == "Focus mode: Automatic")
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 0);
        ui -> focusButton -> setText("Focus mode: Manual");

        ui -> focusLabel -> setEnabled(true);
        ui -> focusSlider -> setEnabled(true);
        ui -> focusOptionsBtn -> setEnabled(true);
    }
    else
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 1);
        ui -> focusButton -> setText("Focus mode: Automatic");

        ui -> focusLabel -> setEnabled(false);
        ui -> focusSlider -> setEnabled(false);
        ui -> focusOptionsBtn -> setEnabled(false);
    }
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
    _camObj.setParam(CAP_PROP_ZOOM, 0);
    _camObj.setParam(CAP_PROP_FOCUS, 128);
}

void MainWindow::defaultUIVals()
{
    ui->contrastSlider->setValue(128);
    ui->brightnessSlider->setValue(128);
    ui->saturationSlider->setValue(128);
    ui->focusSlider->setValue(128);
    ui->zoomSlider->setValue(0);
}

void MainWindow::on_modeButton_pressed()
{
    if (ui->modeButton->text() == "Current mode: Dynamic")
    {
        if (ui->calibrationLabel->text() != "*Uncalibrated*")
        {
            ui->modeButton->setText("Current mode: Static");
            _videoFPSTimer.stop();

            ui->positionCalibrationButton->setEnabled(false);

            ui->adjustmentsGroup->setTitle("Adjustments Group");
            ui->algorithmsGroup->setTitle("*Algorithms group");

            ui->modesLabel->setText("Measurement");
            ui->modesLabel->setStyleSheet("QLabel { background-color : green; color : white; }");

            ui->captureButton->setEnabled(true);
            ui->adjustmentsGroup->setEnabled(false);
            ui->algorithmsGroup->setEnabled(true);
        }
        else
        {
            if (Errors::cameraPositionUncalibrated() == 0)
            {
                on_positionCalibrationButton_pressed();
            }
        }
    }
    else
    {
        ui->modeButton->setText("Current mode: Dynamic");
        _videoFPSTimer.start();

        ui->positionCalibrationButton->setEnabled(true);

        ui->adjustmentsGroup->setTitle("*Adjustments Group");
        ui->algorithmsGroup->setTitle("Algorithms group");

        ui->modesLabel->setText("Inspection");
        ui->modesLabel->setStyleSheet("QLabel { background-color : orange; color : black; }");

        ui->captureButton->setEnabled(false);
        ui->adjustmentsGroup->setEnabled(true);
        ui->algorithmsGroup->setEnabled(false);
    }
}

void MainWindow::on_positionCalibrationButton_pressed()
{
    if(ui->positionCalibrationButton->text() == "Position calibration")
    {
        if(!_ardSerial.serialIsConnected(ARDUINO_VENDOR_ID, ARDUINO_PRODUCT_ID))
        {
            Errors::serialConnectionError();
        }

        setOptionsButtons(false);
        switchAlgToGantry(true);

        if (!_videoFPSTimer.isActive())
            _videoFPSTimer.start();

        ui->positionCalibrationButton->setText("*Confirm calibration*");
        ui->calibrationLabel->setText("Calibrating...");

        ui->positionCalibrationButton->setStyleSheet("background-color: cyan");
        setMeasurementButtons(false);

        _calibrationInProgress = true;
    }
    else
    {
        setOptionsButtons(true);
        switchAlgToGantry(false);

        if (ui->modeButton->text() == "Current mode: Static")
            _videoFPSTimer.stop();

        ui->positionCalibrationButton->setText("Position calibration");
        ui->positionCalibrationButton->setStyleSheet("background-color: lightGray");

        ui->calibrationLabel->setText(">Calibrated<");
        setMeasurementButtons(true);

        _calibrationInProgress = false;
    }
}

void MainWindow::setOptionsButtons(bool val)
{
    ui->modeButton->setEnabled(val);
    ui->captureButton->setEnabled(val);
}

void MainWindow::setMeasurementButtons(bool val)
{
    ui->measureButton->setEnabled(val);
    ui->detailMergeButton->setEnabled(val);
    ui->stackImagesButton->setEnabled(val);
    ui->edgeDetectButton->setEnabled(val);
}

void MainWindow::on_actionFull_screen_triggered(bool checked)
{
    if (checked)
    {
        MainWindow::window()->setWindowState(Qt::WindowFullScreen);
        ui->actionCenter_window->setEnabled(false);
    }
    else
    {
        MainWindow::window()->setWindowState(Qt::WindowNoState);
        ui->actionCenter_window->setEnabled(true);
    }

    resizeLabelToWindow();
}

void MainWindow::on_actionCenter_window_triggered()
{
    centerWindow();
}

void MainWindow::on_contrastSlider_sliderMoved(int position)
{
    _camObj.setParam(CAP_PROP_CONTRAST, position);
}

void MainWindow::on_brightnessSlider_sliderMoved(int position)
{
    _camObj.setParam(CAP_PROP_BRIGHTNESS, position);
}

void MainWindow::on_saturationSlider_sliderMoved(int position)
{
    _camObj.setParam(CAP_PROP_SATURATION, position);
}

void MainWindow::on_zoomSlider_sliderMoved(int position)
{
    _camObj.setParam(CAP_PROP_ZOOM, position + 100);
}

void MainWindow::on_focusSlider_sliderMoved(int position)
{
    _camObj.setParam(CAP_PROP_FOCUS, position * 5);
}

void MainWindow::on_contrastOptionsBtn_pressed()
{
    _camObj.setParam(CAP_PROP_CONTRAST, 128);
    ui -> contrastSlider -> setValue(128);
}

void MainWindow::on_brightnessOptionsBtn_pressed()
{
    _camObj.setParam(CAP_PROP_BRIGHTNESS, 128);
    ui -> brightnessSlider -> setValue(128);
}

void MainWindow::on_saturationOptionsBtn_pressed()
{
    _camObj.setParam(CAP_PROP_SATURATION, 128);
    ui -> saturationSlider -> setValue(128);
}

void MainWindow::on_zoomOptionsBtn_pressed()
{
    _camObj.setParam(CAP_PROP_ZOOM, 100);
    ui -> zoomSlider -> setValue(0);
}

void MainWindow::on_focusOptionsBtn_pressed()
{
    _camObj.setParam(CAP_PROP_FOCUS, 100);
    ui -> focusSlider -> setValue(20);
}

void MainWindow::on_measureButton_pressed()
{
    emit sendGlobalMat(_camObj.retrieveGlobalUndistortedFrame(_res_Width), QSize(_res_Width, _res_Height), _screenGeometry);

    _measuringInterface -> setModal(true);
    _measuringInterface -> exec();
}

void MainWindow::on_captureButton_pressed()
{
    captureImage();
    captureImage(); // Second capture to flush the buffer

    ui->distortionLabel->setText("Undistorted");
}

void MainWindow::on_distortionButton_pressed()
{
    Mat undistortedMat = _camObj.retrieveGlobalUndistortedFrame(_res_Width);
    ui->videoLabel->setPixmap( _camObj.convertMatToQPixmap(undistortedMat) );

    ui->distortionLabel->setText("Undistorted");
}

void MainWindow::on_lensCorrectioncheckBox_stateChanged(int arg1)
{
    _liveLensCorrection = arg1;
}

void MainWindow::on_actionEnumerate_Ports_triggered()
{
    QList<QString> enumsList = _ardSerial.getSerialEnumerations();
    QMessageBox msgBox;

    if (enumsList.count() > 0)
    {
        for(int i = 0; i < enumsList.count(); i++)
        {
            msgBox.setText("Serial ports enumeration");
            msgBox.setInformativeText(enumsList[i]);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
        }

        if (!_ardSerial.serialIsConnected(ARDUINO_VENDOR_ID, ARDUINO_PRODUCT_ID))
        {
            msgBox.setText("One or more Serial ports found");
            msgBox.setInformativeText("Would you like to try and to make a Serial connection with the Arduino board?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);

            int ret = msgBox.exec();

            switch (ret)
            {
                case QMessageBox::Yes:
                {
                    _ardSerial.connectToSerial(ARDUINO_VENDOR_ID, ARDUINO_PRODUCT_ID);
                    break;
                }
                case QMessageBox::No:
                {
                    qDebug() << "User chose not to attempt a Serial connection to the available Port(s).";
                    break;
                }
                default:
                    qDebug() << "User exited from the Serial connection prompt after enumerating the Serial ports.";
            }
        }
    }
    else
    {
        Errors::serialNoEnumsFound();
    }

    return;
}

void MainWindow::on_actionAttempt_to_connect_triggered()
{
    QMessageBox msgBox;
    _ardSerial.connectToSerial(ARDUINO_VENDOR_ID, ARDUINO_PRODUCT_ID);

    if(_ardSerial.serialIsConnected(ARDUINO_VENDOR_ID, ARDUINO_PRODUCT_ID))
    {
        msgBox.setText("Serial ports enumeration");
        msgBox.setInformativeText("Successfully connected to the board: " + QString::fromStdString(ARDUINO_VENDOR_ID) + " " + QString::fromStdString(ARDUINO_PRODUCT_ID));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        Errors::serialNoEnumsFound();
    }
}

void MainWindow::on_actionCheck_connection_status_triggered()
{
    QMessageBox msgBox;

    msgBox.setText("Serial port connection status:");
    int status = _ardSerial.serialIsConnected(ARDUINO_VENDOR_ID, ARDUINO_PRODUCT_ID);

    switch (status)
    {
    case 0:
    {
        msgBox.setInformativeText("The Arduino board is currently NOT connected.\nThe reason for this is that no Serial Ports are found at all.");
        break;
    }
    case 1:
    {
        msgBox.setInformativeText("The Arduino board is currently successfully connected to the system.");
        break;
    }
    case 2:
    {
        msgBox.setInformativeText("The Arduino board is currently located as available Ports, but is not yet Connected to.");
        break;
    }
    case 3:
    {
        msgBox.setInformativeText("There are some Port(s) found on the system, but the Arduino board ID's are not found.\nThe board is not connected.");
        break;
    }
    default:
    {
        msgBox.setInformativeText("ERROR: The status ran into a critical unexpected error!");
    }
    }

    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_LightLevelSlider_sliderMoved(int position)
{
    // qDebug() << "Sending Master Ring light level of: " << position;

    QByteArray converted;
    converted.setNum(position);

    if (position < 255)
    {
        _ardSerial.sendData("RING_R 255");
        _ardSerial.sendData("RING_L " + converted );
    }
    else
    {
        _ardSerial.sendData("RING_R " + converted );
        _ardSerial.sendData("RING_L 0");
    }
}

void MainWindow::on_gantryUpButton_pressed()
{
    if (ui->sensitiveGantryCheckBox->isChecked())
        _ardSerial.sendData("STEP_U6");
    else
        _ardSerial.sendData("STEP_U10");
}

void MainWindow::on_gantryDownButton_pressed()
{
    if (ui->sensitiveGantryCheckBox->isChecked())
        _ardSerial.sendData("STEP_D6");
    else
        _ardSerial.sendData("STEP_D10");
}

void MainWindow::on_gantryLeftButton_pressed()
{
    if (ui->sensitiveGantryCheckBox->isChecked())
        _ardSerial.sendData("STEP_L6");
    else
        _ardSerial.sendData("STEP_L10");
}

void MainWindow::on_gantryRightButton_pressed()
{
    if (ui->sensitiveGantryCheckBox->isChecked())
        _ardSerial.sendData("STEP_R6");
    else
        _ardSerial.sendData("STEP_R10");
}

void MainWindow::on_ringLightOnButton_pressed()
{
    _ardSerial.sendData("RING_ON");
}

void MainWindow::on_ringLightOffButton_pressed()
{
    _ardSerial.sendData("RING_OFF");
}
