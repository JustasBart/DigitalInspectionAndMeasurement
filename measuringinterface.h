#ifndef MEASURINGINTERFACE_H
#define MEASURINGINTERFACE_H

#include <stdlib.h>
#include <QDialog>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QDebug>
#include <QFileDialog>
#include <grid.h>

using namespace cv;

namespace Ui
{
    class MeasuringInterface;
}

class MeasuringInterface : public QDialog
{
    Q_OBJECT

public:
    explicit MeasuringInterface(QWidget *parent = nullptr);
    ~MeasuringInterface();

public slots:
    void receiveCurrentMat(Mat currentFrame, QRect screenSize);

private slots:
    void on_saveImageButton_pressed();
    void on_drawGridCheckbox_stateChanged(int arg1);
    void on_gridSlider_sliderMoved(int position);

private:
    Ui::MeasuringInterface *ui;

    QPixmap matToPixmap(Mat frame);
    void resizeWindowToScreenSize();
    void resizeLabelToWindow();
    void updateFrame(Mat newFrame);

    Mat _workingFrame;
    Mat _frameWithGrid;

    QPixmap _workingPixmap;
    int _screenWidth;
    int _screenHeight;
};

#endif // MEASURINGINTERFACE_H
