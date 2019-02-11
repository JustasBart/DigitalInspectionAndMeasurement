#include "measuringinterface.h"
#include "ui_measuringinterface.h"

using namespace cv;

MeasuringInterface::MeasuringInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasuringInterface),
    _workingFrame({0})
{
    ui->setupUi(this);


}

MeasuringInterface::~MeasuringInterface()
{
    delete ui;
}

void MeasuringInterface::receiveCurrentMat(Mat currentFrame)
{
    _workingFrame = currentFrame;
}
