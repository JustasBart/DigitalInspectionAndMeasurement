#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/highgui/highgui.hpp>
#include <QDebug>
#include <QString>

using namespace cv;

class Camera
{
public:
    static void cameraInit(VideoCapture &cameraObj, unsigned char fps);
    static void setParam(VideoCapture &cameraObj, cv::VideoCaptureProperties property, unsigned char value);
};

#endif // CAMERA_H
