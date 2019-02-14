#include "measuringinterface.h"
#include "ui_measuringinterface.h"

void MeasuringInterface::on_drawGridCheckbox_stateChanged(int arg1)
{
    if (arg1)
    {
        ui->gridSizeLabel->setEnabled(true);
        ui->gridSlider->setEnabled(true);

        on_gridSlider_sliderMoved( ui->gridSlider->value() );
    }
    else
    {
        ui->gridSizeLabel->setEnabled(false);
        ui->gridSlider->setEnabled(false);

        updateFrame( _workingFrame );
    }
}

void MeasuringInterface::on_gridSlider_sliderMoved(int position)
{
    _frameWithGrid = _workingFrame.clone();
    Grid::placeGrid( _frameWithGrid, position );
    updateFrame( _frameWithGrid );
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
