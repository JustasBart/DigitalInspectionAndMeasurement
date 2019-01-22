#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    startUpDialog(new StartupDialog),
    _camPort(0),
    _fullScreen(false),
    _res_Width(1920),
    _res_Height(1080),
    _fps(30)
{
    connect(startUpDialog, SIGNAL(sendData(unsigned int, QString)), this, SLOT(receiveData(unsigned int, QString)));
    startUpDialog -> exec();
    ui -> setupUi(this);

    MainWindow::init();
}

MainWindow::~MainWindow()
{
    // saveGUISettings();

    delete ui;
}
