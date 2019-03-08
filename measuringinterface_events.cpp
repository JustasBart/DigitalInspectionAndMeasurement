#include "measuringinterface.h"
#include "ui_measuringinterface.h"

void MeasuringInterface::on_drawGridCheckbox_stateChanged(int arg1)
{
    if (arg1)
    {
        ui->gridSizeLabel->setEnabled(true);
        ui->gridSlider->setEnabled(true);
        ui->smallGridSlider->setEnabled(true);

        on_gridSlider_sliderMoved( ui->gridSlider->value() );
        hideScaleLine();
    }
    else
    {
        ui->gridSizeLabel->setEnabled(false);
        ui->gridSlider->setEnabled(false);
        ui->smallGridSlider->setEnabled(false);

        updateFrame( _workingFrame );
    }
}

void MeasuringInterface::on_gridSlider_sliderMoved(int position)
{
    int gridSize = (position * 2) + ui->smallGridSlider->value();

    _frameWithGrid = _workingFrame.clone();
    HelperClass::placeGrid( _frameWithGrid, gridSize );
    updateGridSizeLabel( gridSize );
    updateFrame( _frameWithGrid );
}

void MeasuringInterface::on_smallGridSlider_sliderMoved(int position)
{
    on_gridSlider_sliderMoved( ui->gridSlider->value() );
    qDebug() << "Smaller slider position: " << position;
}

void MeasuringInterface::on_saveImageButton_pressed()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save image"), "/Desktop/image",
            tr("JPEG (*.jpg);;PNG *.png;;BITMAP *.bmp"));

    if (!fileName.isEmpty())
        cv::imwrite( fileName.toStdString().c_str(), _workingFrame );
    else
        qDebug() << "Saving image canceled by the user.";
}

void MeasuringInterface::on_drawScaleButton_pressed()
{
    if (ui->drawScaleButton->text() == "Draw scale")
    {
        updateFrame(_workingFrame);
        ui->drawScaleButton->setText("Drawing scale");
        ui->drawScaleButton->setEnabled(false);
        ui->scaledLabel->setStyleSheet("QLabel { background-color : orange; color : white; }");
        ui->scaledLabel->setText("Drawing - Point 1");
        _scaleDrawingStatus = true;
    }
}

void MeasuringInterface::on_removeScaleButton_pressed()
{
    updateFrame(_workingFrame);
    ui->removeScaleButton->setEnabled(false);
}

void MeasuringInterface::on_mmSpinbox_valueChanged(int arg1)
{
    _PXtoMM = LinesClass::calculatePXtoMM(_mappedPoint1, _mappedPoint2, arg1);
    updateGridSizeLabel(arg1);
    ui->px_mmValueLabel->setText("Current PX/MM value: " + QString::number(_PXtoMM));
}

void MeasuringInterface::updateGridSizeLabel(int pixels)
{
    if (ui->drawGridCheckbox->checkState() == Qt::Checked && _PXtoMM != 0.0)
        ui->gridSizeLabel->setText("Grid size: " + QString::number( pixels / _PXtoMM, 'g', 4 ) + "mm");
}

void MeasuringInterface::on_drawRulerButton_pressed()
{
    ui->statusLabel->setText("Status: Drawing - Point 1");
    ui->statusLabel->setStyleSheet("QLabel { background-color : red; color : white; }");
    _rulerDrawingStatus = true;

    ui->drawGridCheckbox->setCheckState(Qt::Unchecked);

    hideScaleLine();
}

void MeasuringInterface::hideScaleLine()
{
    if (ui->removeScaleButton->isEnabled())
    {
        updateFrame(_workingFrame);
        ui->removeScaleButton->setEnabled(false);
    }
}

void MeasuringInterface::labelMouseClickedPos(QPoint &pos)
{
    if (_rulerDrawingStatus)
    {
        if (ui->statusLabel->text() == "Status: Drawing - Point 1")
        {
            _tempPoint1 = pos;
            ui->statusLabel->setText("Status: Drawing - Point 2");
            ui->statusLabel->setStyleSheet("QLabel { background-color : green; color : white; }");
        }
        else
        {
            _tempPoint2 = pos;
            ui->statusLabel->setText("Status:");
            ui->statusLabel->setStyleSheet("QLabel { background-color : transparent; color : black; }");

            _rulerDrawingStatus = false;

            _frameWithRulers = _workingFrame.clone();
            _lClassObj->addRuler(_frameWithRulers, _tempPoint1, _tempPoint2, ui->frameLabel->size(), QSize(_workingFrame.cols, _workingFrame.rows), _PXtoMM);
            emit sendTableObject(*ui->rulersTable);
            updateFrame(_frameWithRulers);
        }
    }
    else if (_scaleDrawingStatus)
    {
        if (ui->scaledLabel->text() == "Drawing - Point 1")
        {
            _tempPoint1 = pos;
            ui->scaledLabel->setText("Drawing - Point 2");
            ui->scaledLabel->setStyleSheet("QLabel { background-color : green; color : white; }");
        }
        else
        {
            _tempPoint2 = pos;
            ui->scaledLabel->setText("Reference scaled");
            ui->scaledLabel->setStyleSheet("QLabel { background-color : transparent; color : black; }");

            ui->drawScaleButton->setText("Draw scale");
            ui->drawScaleButton->setEnabled(true);
            _scaleDrawingStatus = false;

            _mappedPoint1.setX( HelperClass::map(_tempPoint1.x(), 0, ui->frameLabel->width(), 0, _workingFrame.cols) );
            _mappedPoint1.setY( HelperClass::map(_tempPoint1.y(), 0, ui->frameLabel->height(), 0, _workingFrame.rows) );

            _mappedPoint2.setX( HelperClass::map(_tempPoint2.x(), 0, ui->frameLabel->width(), 0, _workingFrame.cols) );
            _mappedPoint2.setY( HelperClass::map(_tempPoint2.y(), 0, ui->frameLabel->height(), 0, _workingFrame.rows) );

            _frameWithScale = _workingFrame.clone();
            cv::line(_frameWithScale, cv::Point2d(_mappedPoint1.x(), _mappedPoint1.y()), cv::Point2d(_mappedPoint2.x(), _mappedPoint2.y()), cv::Scalar(35, 255, 214), 5, 4);
            updateFrame(_frameWithScale);

            ui->removeScaleButton->setEnabled(true);

            _PXtoMM = LinesClass::calculatePXtoMM(_mappedPoint1, _mappedPoint2, ui->mmSpinbox->value());
            ui->px_mmValueLabel->setText("Current PX/MM value: " + QString::number(_PXtoMM));

            ui->drawGridCheckbox->setEnabled(true);
            ui->drawRulerButton->setEnabled(true);
        }
    }
}
