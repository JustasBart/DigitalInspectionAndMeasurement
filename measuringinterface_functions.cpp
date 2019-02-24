#include "measuringinterface.h"
#include "ui_measuringinterface.h"

void MeasuringInterface::receiveCurrentMat(Mat currentFrame, QSize frameRes, QRect screenSize)
{
    qDebug() << "Received the frame for measuring...";

    _workingFrame = currentFrame.clone();
    _workingPixmap = matToPixmap(_workingFrame);

    _screenWidth  = screenSize.width();
    _screenHeight = screenSize.height();

    _frameWidth = frameRes.width();
    _frameHeight = frameRes.height();

    if (!_workingPixmap.isNull())
        updateFrame(currentFrame);
    else
        qDebug() << "The input frame is invalid!";

    resizeWindowToScreenSize();
    resizeLabelToWindow();
}

void MeasuringInterface::labelMousePos(QPoint &pos)
{
    if (ui->drawScaleButton->text() == "Draw scale")
        ui->scaledLabel->setText("x: " + QString::number(pos.x()) + ", y: " + QString::number(pos.y()));
}

void MeasuringInterface::labelMouseClickedPos(QPoint &pos)
{
    if (ui->drawScaleButton->text() != "Draw scale")
    {
        qDebug() << "Clicked pos: x: " << QString::number(pos.x()) + ", y: " + QString::number(pos.y());

        if (_scaleDrawingIndex == 0)
        {
            _scaleLinePoints[0] = pos;
            ui->scaledLabel->setText("Point 2");
        }
        else if (_scaleDrawingIndex == 1)
        {
            _scaleLinePoints[1] = pos;
            ui->scaledLabel->setText("Drawing line");

            qDebug() << "Point 1: " << _scaleLinePoints[0] << " Point 2: " << _scaleLinePoints[1];

            drawLine();

            ui->removeScaleButton->setEnabled(true);
            ui->drawScaleButton->setText("Draw scale");
        }

        _scaleDrawingIndex++;
    }
}

void MeasuringInterface::drawLine()
{
    _frameWithScale = _workingFrame.clone();

    _mappedPoint1.x = HelperClass::map(_scaleLinePoints[0].x(), 0, ui->frameLabel->width(), 0, _frameWidth);
    _mappedPoint1.y = HelperClass::map(_scaleLinePoints[0].y(), 0, ui->frameLabel->height(), 0, _frameHeight);

    qDebug() << _frameWidth << " and " << _frameHeight;

    _mappedPoint2.x = HelperClass::map(_scaleLinePoints[1].x(), 0, ui->frameLabel->width(), 0, _frameWidth);
    _mappedPoint2.y = HelperClass::map(_scaleLinePoints[1].y(), 0, ui->frameLabel->height(), 0, _frameHeight);

    cv::line(_frameWithScale, _mappedPoint1, _mappedPoint2, cv::Scalar(255, 255, 0));

    _PXtoMM = calculatePXtoMM(_mappedPoint1, _mappedPoint2, ui->mmSpinbox->value());
    ui->px_mmValueLabel->setText("Current PX/MM value: " + QString::number(_PXtoMM));

    qDebug() << _PXtoMM;

    updateFrame( _frameWithScale );
}

double MeasuringInterface::calculatePXtoMM(cv::Point p1, cv::Point p2, int distance)
{
    return qSqrt( qPow(p1.x - p2.x, 2) + qPow(p1.y - p2.y, 2) ) / distance;
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

void MeasuringInterface::updateFrame(Mat newFrame)
{
    ui -> frameLabel -> setPixmap( matToPixmap(newFrame) );
}
