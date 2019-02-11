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

void MeasuringInterface::receiveCurrentMat(Mat currentFrame, QRect screenSize)
{
    qDebug() << "Received the frame for measuring...";
    _workingFrame = currentFrame;
    _workingPixmap = matToPixmap(_workingFrame);

    _screenWidth  = screenSize.width();
    _screenHeight = screenSize.height();

    if (!_workingPixmap.isNull())
        ui -> frameLabel -> setPixmap( _workingPixmap );
    else
        qDebug() << "The input frame is invalid!";

    resizeWindowToScreenSize();
    resizeLabelToWindow();
}

QPixmap MeasuringInterface::matToPixmap(Mat frame)
{
    Mat tempMat;
    cv::cvtColor(frame, tempMat, CV_BGR2RGB);
    QImage dest(static_cast<const uchar *>(tempMat.data), tempMat.cols, tempMat.rows, static_cast<int>(tempMat.step), QImage::Format_RGB888);
    dest.bits();

    return QPixmap::fromImage(dest);
}

void MeasuringInterface::resizeWindowToScreenSize()
{
    this->setFixedWidth( _screenWidth * 3/4 + ui->sideFrame->width() );
    this->setFixedHeight( _screenHeight * 3/4 + 10 );
}

void MeasuringInterface::resizeLabelToWindow()
{
    int calculatedWidth = this->width() - ui->sideFrame->width() - 40;

    ui->frameLabel->setFixedWidth( calculatedWidth );
    ui->frameLabel->setFixedHeight( static_cast<int>(calculatedWidth / (16.0/9.0)) );
}
