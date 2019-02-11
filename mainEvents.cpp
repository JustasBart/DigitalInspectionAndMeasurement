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

void MainWindow::on_modeButton_clicked()
{
    if (ui->modeButton->text() == "Current mode: Dynamic")
    {
        ui->modeButton->setText("Current mode: Static");
        _videoFPSTimer.stop();

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
        ui->modeButton->setText("Current mode: Dynamic");
        _videoFPSTimer.start();

        ui->adjustmentsGroup->setTitle("*Adjustments Group");
        ui->algorithmsGroup->setTitle("Algorithms group");

        ui->modesLabel->setText("Inspection");
        ui->modesLabel->setStyleSheet("QLabel { background-color : orange; color : black; }");

        ui->captureButton->setEnabled(false);
        ui->adjustmentsGroup->setEnabled(true);
        ui->algorithmsGroup->setEnabled(false);
    }
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
    emit sendGlobalMat(_camObj.retrieveGlobalFrame());
    _measuringInterface -> setModal(true);
    _measuringInterface -> exec();
}

void MainWindow::on_captureButton_pressed()
{
    captureImage();
}
