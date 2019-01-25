#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _startUpDialog(new StartupDialog),
    _screen(QGuiApplication::primaryScreen()),
    _screenGeometry(_screen->geometry()),
    _camPort(0),
    _savePreferences(false),
    _fullScreen(false),
    _res_Width(0),
    _res_Height(0),
    _fps(0),
    _calibrationInProgress(false)
{
    connect(_startUpDialog, SIGNAL(sendData(unsigned int, QString)), this, SLOT(receiveData(unsigned int, QString)));
    _startUpDialog -> exec();

    ui -> setupUi(this);

    MainWindow::init();
}

MainWindow::~MainWindow()
{
    _videoFPSTimer.stop();

    if (_savePreferences)
    {
        saveGUISettings();
    }

    delete ui;
}
