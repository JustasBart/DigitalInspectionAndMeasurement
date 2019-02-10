#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    ui->actionFull_screen->setChecked( _fullScreen );
    ui->modesLabel->setStyleSheet("QLabel { background-color : orange; color : black; }");
    ui->calibrationGroup->setVisible(false);
    ui->calibrationGroup->setEnabled(false);

    resizeWindowToScreenSize();
    resizeLabelToWindow();

    centerWindow();

    if (_camObj.cameraInit(_camPort, _fps, _res_Width, _res_Height) == -1)
    {
        if (_camObj.cameraInit(0, _fps, _res_Width, _res_Height) == -1)
            Errors::fatalError("The camera cannot be initialized.");
    }

    ui->fpsLabel->setText( "Frames per second: " + QString::number(_camObj.getFPS()) );

    connect(&_videoFPSTimer, SIGNAL(timeout()), MainWindow::window(), SLOT(captureImage()));
    _videoFPSTimer.start(1000 / _fps);

    if (_savePreferences) loadGUISettings();
}

void MainWindow::resizeWindowToScreenSize()
{
    MainWindow::window()->setFixedWidth( _screenGeometry.width() * 2/3 );
    MainWindow::window()->setFixedHeight( _screenGeometry.height() * 3/4 - 20 );
}

void MainWindow::resizeLabelToWindow()
{
    ui->videoLabel->heightForWidth(16/9);
    ui->videoLabel->setMinimumWidth( this->width() - ui->adjustmentsGroup->width() - 30 );
}

void MainWindow::centerWindow()
{
    if (_fullScreen)
    {
        MainWindow::window()->setWindowState(Qt::WindowFullScreen);
    }
    else
    {   
        MainWindow::window()->setGeometry(
            QStyle::alignedRect(
                Qt::LeftToRight,
                Qt::AlignCenter,
                MainWindow::window()->size(),
                QRect(0, 0, _screenGeometry.size().width(), _screenGeometry.size().height())
            )
        );
    }
}

void MainWindow::captureImage()
{
    _globalFrame = _camObj.captureImage();

    if (_calibrationInProgress)
        Measurements::drawCalibrationLines( &_globalFrame );

    ui -> videoLabel -> setPixmap( _globalFrame );
}

void MainWindow::loadGUISettings()
{
    QVariant settingsVar;

    settingsVar = UserSettings::loadSettings("Contrast", 0, GROUP_LOCATION);
    ui->contrastSpinBox->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Brightness", 0, GROUP_LOCATION);
    ui->brightnesSpinBox->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Saturation", 0, GROUP_LOCATION);
    ui->saturationSpinBox->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Zoom", 0, GROUP_LOCATION);
    ui->zoomSpinBox->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Focus", 0, GROUP_LOCATION);
    ui->focusSpinBox->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("FocusMode", 0, GROUP_LOCATION);
    if (settingsVar.toBool())
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 1);
        ui -> focusButton -> setText("Focus mode: Automatic");
        ui -> focusLabel -> setEnabled(false);
        ui -> focusSpinBox -> setEnabled(false);
    }
    else
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 0);
        ui -> focusButton -> setText("Focus mode: Manual");
        ui -> focusLabel -> setEnabled(true);
        ui -> focusSpinBox -> setEnabled(true);
    }
}

void MainWindow::saveGUISettings()
{
    UserSettings::saveSettings("Contrast", ui->contrastSpinBox->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Brightness", ui->brightnesSpinBox->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Saturation", ui->saturationSpinBox->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Zoom", ui->zoomSpinBox->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Focus", ui->focusSpinBox->value(), GROUP_LOCATION);
    if (ui->focusButton->text() == "Focus mode: Automatic")
        UserSettings::saveSettings("FocusMode", true, GROUP_LOCATION);
    else
        UserSettings::saveSettings("FocusMode", false, GROUP_LOCATION);
}

void MainWindow::receiveData(unsigned int val, QString param)
{
    switch (val)
    {
        case 0:
        {
            _camPort = param.toInt();
            break;
        }
        case 1:
        {
            QStringList resWH = param.split("x");

            _res_Width =  resWH[0].trimmed().toInt();
            _res_Height = resWH[1].trimmed().toInt();

            break;
        }
        case 2:
        {
            _fps = param.toInt();
            break;
        }
        case 3:
        {
            _fullScreen = param.toInt();
            break;
        }
        case 4:
        {
            _savePreferences = param.toInt();
            break;
        }
        default:
        {
            qDebug() << "Unrecognised command [" << val << "] received";
            break;
        }
    }
}
