#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _startUpDialog(new StartupDialog),
    _measuringInterface(new MeasuringInterface),
    _screen(QGuiApplication::primaryScreen()),
    _screenGeometry(_screen->geometry()),
    _camPort(0),
    _savePreferences(false),
    _fullScreen(false),
    _res_Width(640),
    _res_Height(480),
    _fps(60),
    _calibrationInProgress(false),
    _liveLensCorrection(false)
{
    connect(_startUpDialog, SIGNAL(sendData(unsigned int, QString)), this, SLOT(receiveData(unsigned int, QString)));
    _startUpDialog -> exec();
    ui -> setupUi(this);

    MainWindow::setWindowFlags(Qt::WindowContextHelpButtonHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    MainWindow::init();
}

MainWindow::~MainWindow()
{
    _camObj.releaseCamera();
    _videoFPSTimer.stop();

    if (_savePreferences)
    {
        saveGUISettings();
    }

    delete ui;
}
