#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/highgui/highgui.hpp>
#include <QDebug>

using namespace cv;

class Camera
{
public:
    Camera();

    static void cameraInit(VideoCapture &cameraObj, unsigned int fps);
};

#endif // CAMERA_H
