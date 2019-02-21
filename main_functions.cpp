#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    ui->actionFull_screen->setChecked( _fullScreen );
    ui->modesLabel->setStyleSheet("QLabel { background-color : orange; color : black; }");

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
    connect(MainWindow::window(), SIGNAL(sendGlobalMat(Mat, QRect)), _measuringInterface, SLOT(receiveCurrentMat(Mat, QRect)));

    _camObj.setBufferSize(0);

    _videoFPSTimer.start(1000 / _fps);

    if (_savePreferences) loadGUISettings();
}

void MainWindow::resizeWindowToScreenSize()
{
    MainWindow::window()->setFixedWidth( _screenGeometry.width() * 3/4 + ui->adjustmentsGroup->width() );
    MainWindow::window()->setFixedHeight( _screenGeometry.height() * 3/4 + 20);
}

void MainWindow::resizeLabelToWindow()
{
    int calculatedWidth = this->width() - ui->adjustmentsGroup->width() - 45;

    ui->videoLabel->setFixedWidth( calculatedWidth );
    ui->videoLabel->setFixedHeight( static_cast<int>(calculatedWidth / (16.0/9.0)) );
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
    _globalFrame = _camObj.captureFrameMat();

    if (_calibrationInProgress)
    {
        _globalQPixmap = _camObj.convertMatToQPixmap(_globalFrame);

        drawCalibrationLines( &_globalQPixmap );

        // DynamicLine::drawLine( &_globalQPixmap );
    }
    else
    {
        _globalQPixmap = _camObj.convertMatToQPixmap(_globalFrame);
    }

    ui -> videoLabel -> setPixmap( _globalQPixmap );
}

void MainWindow::loadGUISettings()
{
    QVariant settingsVar;

    settingsVar = UserSettings::loadSettings("Contrast", 0, GROUP_LOCATION);
    ui->contrastSlider->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Brightness", 0, GROUP_LOCATION);
    ui->brightnessSlider->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Saturation", 0, GROUP_LOCATION);
    ui->saturationSlider->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Zoom", 0, GROUP_LOCATION);
    ui->zoomSlider->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("Focus", 0, GROUP_LOCATION);
    ui->focusSlider->setValue( settingsVar.toInt() );
    settingsVar = UserSettings::loadSettings("FocusMode", 0, GROUP_LOCATION);
    if (settingsVar.toBool())
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 1);
        ui -> focusButton -> setText("Focus mode: Automatic");
        ui -> focusLabel -> setEnabled(false);
        ui -> focusSlider -> setEnabled(false);
    }
    else
    {
        _camObj.setParam(CAP_PROP_AUTOFOCUS, 0);
        ui -> focusButton -> setText("Focus mode: Manual");
        ui -> focusLabel -> setEnabled(true);
        ui -> focusSlider -> setEnabled(true);
    }
}

void MainWindow::saveGUISettings()
{
    UserSettings::saveSettings("Contrast", ui->contrastSlider->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Brightness", ui->brightnessSlider->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Saturation", ui->saturationSlider->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Zoom", ui->zoomSlider->value(), GROUP_LOCATION);
    UserSettings::saveSettings("Focus", ui->focusSlider->value(), GROUP_LOCATION);
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

void MainWindow::drawCalibrationLines(QPixmap *frameToDrawOn)
{
    QPainter painter(frameToDrawOn);

    int width = frameToDrawOn->width();
    int height = frameToDrawOn->height();

    int lineThickness = static_cast<int>( frameToDrawOn->width() * 0.0045 );
    int offset = static_cast<int>( frameToDrawOn->width() * 0.02 );

    painter.setPen(QPen( Qt::red, lineThickness, Qt::DashLine, Qt::RoundCap) );

    for (int i = 1; i <= 4; i++)
    {
        painter.drawLine(offset*i, offset*i, offset*i, height - offset*i);
        painter.drawLine(width - offset*i, offset*i, width - offset*i, height - offset*i);
    }

    painter.setPen(QPen( Qt::blue, lineThickness - 2, Qt::SolidLine, Qt::RoundCap) );

    painter.drawLine(offset + 5, offset, width - offset,  height - offset - 5);
    painter.drawLine(width - offset - 5, offset, offset + 2, height - offset - 5);

    painter.drawLine(width/2, height/2 + offset*10, width/2, height/2 - offset*10);

    painter.setPen(QPen( Qt::green, lineThickness - 2, Qt::SolidLine, Qt::RoundCap) );

    painter.drawLine(width/2 - offset*6, height/2 - offset*10, width/2 + offset*6, height/2 - offset*10);
    painter.drawLine(width/2 - offset*6, height/2 + offset*10, width/2 + offset*6, height/2 + offset*10);

    painter.setPen(QPen( Qt::yellow, lineThickness - 2, Qt::SolidLine, Qt::RoundCap) );

    painter.drawLine(offset*5, height/2, width/2 - offset*2, height/2);
    painter.drawLine(width - offset*5, height/2, width/2 + offset*2, height/2);
}