#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    ui->actionFull_screen->setChecked( _fullScreen );

    resizeWindowToScreenSize();
    centerWindow();

    resizeLabelToWindow();

    if (_camObj.cameraInit(_camPort, _fps, _res_Width, _res_Height) == -1)
    {
        if (_camObj.cameraInit(0, _fps, _res_Width, _res_Height) == -1)
            Errors::fatalError("The camera cannot be initialized.");
    }

    ui->fpsLabel->setText( "Frames per second: " + QString::number(_camObj.getFPS()) );

    connect(&_videoFPSTimer, SIGNAL(timeout()), MainWindow::window(), SLOT(captureImage()));
    _videoFPSTimer.start(1000 / _fps);

    // loadGUISettings();
}

void MainWindow::resizeWindowToScreenSize()
{
    MainWindow::window()->setFixedWidth( _screenGeometry.width() * 2/3 );
    MainWindow::window()->setFixedHeight( _screenGeometry.height() * 2/3 );
}

void MainWindow::resizeLabelToWindow()
{
    ui->videoLabel->heightForWidth(16/9);
    ui->videoLabel->setMaximumWidth( this->width() - ui->settingsGroup->width() - 30 );
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
    ui -> videoLabel -> setPixmap( _camObj.captureImage() );
    // ui -> fpsLabel -> setText( QString::number(_camObj.getFPS()) );
}

/*
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
*/

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
            QString resWidth = param.mid(0, 4);
            QString resHeight = param.mid(5, 9);

            _res_Width = resWidth.trimmed().toInt();
            _res_Height = resHeight.trimmed().toInt();
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

void MainWindow::on_actionFull_screen_triggered(bool checked)
{
    if (checked)
        MainWindow::window()->setWindowState(Qt::WindowFullScreen);
    else
        MainWindow::window()->setWindowState(Qt::WindowNoState);

    resizeLabelToWindow();
}
