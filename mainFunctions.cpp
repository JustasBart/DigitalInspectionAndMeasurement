#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    connect(&_videoFPSTimer, SIGNAL(timeout()), MainWindow::window(), SLOT(captureImage()));

    camObj.cameraInit(CAMERA_HARDWARE, FPS);
    _videoFPSTimer.start(1000 / FPS);
    loadGUISettings();
}

void MainWindow::captureImage()
{
    ui -> videoFeed -> setPixmap( camObj.captureImage() );
    ui -> fpsLabel -> setText( QString::number(camObj.getFPS()) );
}

void MainWindow::loadGUISettings()
{
    QVariant settingsVar;
    QString groupSettings = "GUIGroup";

    UserSettings::loadSettings("Contrast", settingsVar, groupSettings);

    qDebug() << "Loading contrast value: " + QString::number(settingsVar.toInt());
    ui->contrastSpinBox->setValue( settingsVar.toInt() );

    UserSettings::loadSettings("Brightness", settingsVar, groupSettings);
    ui->brightnesspinBox->setValue( settingsVar.toInt() );
    UserSettings::loadSettings("Saturation", settingsVar, groupSettings);
    ui->saturationSpinBox->setValue( settingsVar.toInt() );
    UserSettings::loadSettings("Zoom", settingsVar, groupSettings);
    ui->zoomSpinBox->setValue( settingsVar.toInt() );
    UserSettings::loadSettings("FocusMode", settingsVar, groupSettings);
    if (settingsVar.toBool())
    {
        camObj.setParam(CAP_PROP_AUTOFOCUS, 1);
        ui -> focusButton -> setText("Focus: Auto");

        ui -> focusLabel -> setEnabled(false);
        ui -> focusSpinBox -> setEnabled(false);
    }
    else
    {
        camObj.setParam(CAP_PROP_AUTOFOCUS, 0);
        ui -> focusButton -> setText("Focus: Manual");

        ui -> focusLabel -> setEnabled(true);
        ui -> focusSpinBox -> setEnabled(true);
    }
    UserSettings::loadSettings("Focus", settingsVar, groupSettings);
    ui->focusSpinBox->setValue( settingsVar.toInt() );
}

void MainWindow::saveGUISettings()
{
    QVariant settingsVar;
    QString groupSettings = "GUIGroup";

    qDebug() << "Saving contrast value: " + QString::number(ui->contrastSpinBox->value());

    UserSettings::saveSettings("Contrast", ui->contrastSpinBox->value(), groupSettings);
    UserSettings::saveSettings("Brightness", ui->brightnesspinBox->value(), groupSettings);
    UserSettings::saveSettings("Saturation", ui->saturationSpinBox->value(), groupSettings);
    UserSettings::saveSettings("Zoom", ui->zoomSpinBox->value(), groupSettings);
    if (ui->focusButton->text() == "Focus: Auto")
        UserSettings::saveSettings("FocusMode", true, groupSettings);
    else
        UserSettings::saveSettings("FocusMode", false, groupSettings);
    UserSettings::saveSettings("Focus", ui->zoomSpinBox->value(), groupSettings);
}
