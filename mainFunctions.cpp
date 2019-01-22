#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    _camObj.cameraInit(CAMERA_HARDWARE, FPS);
    connect(&_videoFPSTimer, SIGNAL(timeout()), MainWindow::window(), SLOT(captureImage()));
    _videoFPSTimer.start(1000 / FPS);

    loadGUISettings();
}
void MainWindow::captureImage()
{
    ui -> videoFeed -> setPixmap( _camObj.captureImage() );
    ui -> fpsLabel -> setText( QString::number(_camObj.getFPS()) );
}

void MainWindow::loadGUISettings()
{
    QVariant settingsVar;

    settingsVar = UserSettings::loadSettings("Contrast", 0, GROUP_LOCATION);
    ui->contrastSpinBox->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Brightness", 0, GROUP_LOCATION);
    ui->brightnesspinBox->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Saturation", 0, GROUP_LOCATION);
    ui->saturationSpinBox->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Zoom", 0, GROUP_LOCATION);
    ui->zoomSpinBox->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("FocusMode", 0, GROUP_LOCATION);
    if (settingsVar.toBool())
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 1);
        ui -> focusButton -> setText("Focus: Auto");
        ui -> focusLabel -> setEnabled(false);
        ui -> focusSpinBox -> setEnabled(false);
    }
    else
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 0);
        ui -> focusButton -> setText("Focus: Manual");
        ui -> focusLabel -> setEnabled(true);
        ui -> focusSpinBox -> setEnabled(true);
    }
    settingsVar = UserSettings::loadSettings("Focus", 0, GROUP_LOCATION);
    ui->focusSpinBox->setValue( settingsVar.toInt() );
}

void MainWindow::saveGUISettings()
{
    UserSettings::saveSettings("Contrast", ui->contrastSpinBox->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Brightness", ui->brightnesspinBox->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Saturation", ui->saturationSpinBox->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Zoom", ui->zoomSpinBox->value(), GROUP_LOCATION);
    if (ui->focusButton->text() == "Focus: Auto")
        UserSettings::saveSettings("FocusMode", true, GROUP_LOCATION);
    else
        UserSettings::saveSettings("FocusMode", false, GROUP_LOCATION);
    UserSettings::saveSettings("Focus", ui->focusSpinBox->value(), GROUP_LOCATION);
}
