#ifndef MEASURINGINTERFACE_H
#define MEASURINGINTERFACE_H

#include <QDebug>
#include <QDialog>
#include <QFileDialog>

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include <opencv2/core/utility.hpp>

#include "grid.h"
#include "dynamicline.h"

using namespace cv;
using namespace std;

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
