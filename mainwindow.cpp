#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    // connect(&_videoFPSTimer, SIGNAL(timeout()), this, SLOT(captureImage()));

    MainWindow::init();
}

MainWindow::~MainWindow()
{
    saveGUISettings();
    delete ui;
}
