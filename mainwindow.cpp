#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    connect(&_videoFPSTimer, SIGNAL(timeout()), this, SLOT(captureImage()));
    MainWindow::init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    camObj.cameraInit(CAMERA_HARDWARE, FPS);
    _videoFPSTimer.start(1000 / FPS);
}

void MainWindow::captureImage()
{
    ui -> videoFeed -> setPixmap( camObj.captureImage() );
    ui -> fpsLabel -> setText( QString::number(camObj.getFPS()) );
}

void MainWindow::on_contrastSpinBox_valueChanged(int arg1)
{
    camObj.setParam(CAP_PROP_CONTRAST, arg1);
}

void MainWindow::on_brightnesspinBox_valueChanged(int arg1)
{
    camObj.setParam(CAP_PROP_BRIGHTNESS, arg1);
}

void MainWindow::on_saturationSpinBox_valueChanged(int arg1)
{
    camObj.setParam(CAP_PROP_SATURATION, arg1);
}

void MainWindow::on_focusButton_pressed()
{
    if (ui -> focusButton -> text() == "Focus: Auto")
    {
        camObj.setParam(CAP_PROP_AUTOFOCUS, 0);
        ui -> focusButton -> setText("Focus: Manual");

        ui -> focusLabel -> setEnabled(true);
        ui -> focusSpinBox -> setEnabled(true);
    }
    else
    {
        camObj.setParam(CAP_PROP_AUTOFOCUS, 1);
        ui -> focusButton -> setText("Focus: Auto");

        ui -> focusLabel -> setEnabled(false);
        ui -> focusSpinBox -> setEnabled(false);
    }
}

void MainWindow::on_focusSpinBox_valueChanged(int arg1)
{
    camObj.setParam(CAP_PROP_FOCUS, arg1);
}

void MainWindow::on_zoomSpinBox_valueChanged(int arg1)
{
    camObj.setParam(CAP_PROP_ZOOM, arg1 + 100);
}
