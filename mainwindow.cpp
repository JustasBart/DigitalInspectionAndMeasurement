#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    startUpDialog(new StartupDialog),
    _camPort(0),
    _savePreferences(false),
    _fullScreen(false),
    _res_Width(0),
    _res_Height(0),
    _fps(0)
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
