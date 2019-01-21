#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

static VideoCapture camera(0);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

    MainWindow::init();

    connect(&_videoFPSTimer, SIGNAL(timeout()), this, SLOT(captureImage()));
    _videoFPSTimer.start(1000 / FPS);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    Camera::cameraInit(camera, FPS);
    Algorithms::sayHello();
}

void MainWindow::captureImage()
{
    camera >> _currentFrameMat;
    _currentFramePixmap = MatToQPixmap( _currentFrameMat );
    ui -> videoFeed -> setPixmap( _currentFramePixmap );
    int getFPS = (int)camera.get( CAP_PROP_FPS );
    ui -> fpsLabel -> setText( QString::number(getFPS) );
}

void MainWindow::on_contrastSpinBox_valueChanged(int arg1)
{
    Camera::setParam(camera, CAP_PROP_CONTRAST, arg1);
}

void MainWindow::on_brightnesspinBox_valueChanged(int arg1)
{
    Camera::setParam(camera, CAP_PROP_BRIGHTNESS, arg1);
}

void MainWindow::on_saturationSpinBox_valueChanged(int arg1)
{
    Camera::setParam(camera, CAP_PROP_SATURATION, arg1);
}

void MainWindow::on_focusButton_pressed()
{
    if (ui -> focusButton -> text() == "Focus: Auto")
    {
        Camera::setParam(camera, CAP_PROP_AUTOFOCUS, 0);
        ui -> focusButton -> setText("Focus: Manual");

        ui -> focusLabel -> setEnabled(true);
        ui -> focusSpinBox -> setEnabled(true);
    }
    else
    {
        Camera::setParam(camera, CAP_PROP_AUTOFOCUS, 1);
        ui -> focusButton -> setText("Focus: Auto");

        ui -> focusLabel -> setEnabled(false);
        ui -> focusSpinBox -> setEnabled(false);
    }
}

void MainWindow::on_focusSpinBox_valueChanged(int arg1)
{
    Camera::setParam(camera, CAP_PROP_FOCUS, arg1);
}

void MainWindow::on_zoomSpinBox_valueChanged(int arg1)
{
    Camera::setParam(camera, CAP_PROP_ZOOM, arg1 + 100);
}
