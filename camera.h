#ifndef CAMERA_H
#define CAMERA_H

#include "Qt-OpenCV-AdditionalLibrary.h"
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>
#include <QString>

using namespace cv;

class Camera
{
public:
    void cameraInit(unsigned char camera, unsigned char fps);
    void setParam(VideoCaptureProperties param, unsigned char value);
    unsigned char getParam(cv::VideoCaptureProperties param);
    QPixmap captureImage();
    unsigned char getFPS();

private:
    VideoCapture *_cameraObj;
    Mat _currentFrameMat;
};

#endif // CAMERA_H
