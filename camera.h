#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>
#include <QString>
#include "errors.h"

using namespace cv;

class Camera
{
public:
    int cameraInit(const int camera, const int fps, const int &width, const int &height);
    void setParam(VideoCaptureProperties param, int value);
    unsigned char getParam(cv::VideoCaptureProperties param);
    void setBufferSize(int frames);
    QPixmap captureImage();
    unsigned char getFPS();
    Mat retrieveGlobalFrame();

private:
    QImage Mat2QImage(cv::Mat const &src);
    VideoCapture *_cameraObj;
    Mat _currentFrameMat;
};

#endif // CAMERA_H
