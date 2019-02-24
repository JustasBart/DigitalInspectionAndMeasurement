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
    on_gridSlider_sliderMoved(ui->gridSlider->value());
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
        _scaleDrawingIndex = 0;
        ui->drawScaleButton->setText("Drawing scale");
        ui->scaledLabel->setText("Point 1");
    }
}

void MeasuringInterface::on_removeScaleButton_pressed()
{
    updateFrame(_workingFrame);
    ui->removeScaleButton->setEnabled(false);
}

void MeasuringInterface::on_mmSpinbox_valueChanged(int arg1)
{
    _PXtoMM = calculatePXtoMM(_mappedPoint1, _mappedPoint2, arg1);
    updateGridSizeLabel(arg1);
    ui->px_mmValueLabel->setText("Current PX/MM value: " + QString::number(_PXtoMM));
}

void MeasuringInterface::updateGridSizeLabel(int pixels)
{
    if (ui->drawGridCheckbox->checkState() == Qt::Checked && _PXtoMM != 0.0)
        ui->gridSizeLabel->setText("Grid size: " + QString::number( pixels / _PXtoMM, 'g', 4 ) + "mm");
}
