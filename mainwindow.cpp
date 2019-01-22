#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    startUpDialog(new StartupDialog)
{
    connect(startUpDialog, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));
    startUpDialog -> exec();
    ui -> setupUi(this);

    MainWindow::init();
}

MainWindow::~MainWindow()
{
    // saveGUISettings();

    delete ui;
}
