#include "measuringinterface.h"
#include "ui_measuringinterface.h"

using namespace cv;

MeasuringInterface::MeasuringInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasuringInterface),
    _screenWidth(0),
    _screenHeight(0)
{
    ui->setupUi(this);
}
MeasuringInterface::~MeasuringInterface()
{
    delete ui;
}
