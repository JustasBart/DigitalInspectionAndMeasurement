#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

static VideoCapture camera(0);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

    if (!camera.isOpened())
    {
       qDebug() << "Cannot access the camera.\nProgram will not close down.";
       exit(EXIT_FAILURE);
    }

    // User defined functionality //
    projectSettings.loadSettings();
    Algorithms::sayHello();
    // End

    if (FPS == 60)
    {
        camera.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    }
    else if (FPS == 30)
    {
        camera.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
        camera.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    }

    camera.set(cv::CAP_PROP_AUTOFOCUS, 1);

    camera.set(cv::CAP_PROP_FOURCC, CV_FOURCC('M','J','P','G'));
    camera.set(cv::CAP_PROP_FPS, FPS);
    
    // Setting up the C922 to 1080p @ 30FPS.
    // camera.open(CV_CAP_DSHOW);
    // camera.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    // camera.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
    // camera.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
    // End
    

    connect(&videoFPSTimer, SIGNAL(timeout()), this, SLOT(captureImage()));

    videoFPSTimer.start(1000 / FPS);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::captureImage()
{
    camera >> currentFrameMat;

    currentFramePixmap = MatToQPixmap( currentFrameMat );

    ui -> videoFeed -> setPixmap(currentFramePixmap);

    int getFPS = (int)camera.get(CAP_PROP_FPS);
    ui -> fpsLabel -> setText( QString::number(getFPS) );
}

void MainWindow::on_contrastSpinBox_valueChanged(int arg1)
{
    camera.set(cv::CAP_PROP_CONTRAST, arg1);
}

void MainWindow::on_brightnesspinBox_valueChanged(int arg1)
{
    camera.set(cv::CAP_PROP_BRIGHTNESS, arg1);
}

void MainWindow::on_saturationSpinBox_valueChanged(int arg1)
{
    camera.set(cv::CAP_PROP_SATURATION, arg1);
}

void MainWindow::on_focusButton_pressed()
{
    if (ui -> focusButton -> text() == "Focus: Auto")
    {
        camera.set(cv::CAP_PROP_AUTOFOCUS, 0);
        ui -> focusButton -> setText("Focus: Manual");

        ui -> focusLabel -> setEnabled(true);
        ui -> focusSpinBox -> setEnabled(true);
    }
    else
    {
        camera.set(cv::CAP_PROP_AUTOFOCUS, 1);
        ui -> focusButton -> setText("Focus: Auto");

        ui -> focusLabel -> setEnabled(false);
        ui -> focusSpinBox -> setEnabled(false);
    }
}

void MainWindow::on_focusSpinBox_valueChanged(int arg1)
{
    camera.set(cv::CAP_PROP_FOCUS, arg1);
}

void MainWindow::on_zoomSpinBox_valueChanged(int arg1)
{
    camera.set(cv::CAP_PROP_ZOOM, arg1 + 100);
}
