#include "camera.h"

void Camera::cameraInit(VideoCapture &cameraObj, unsigned char fps)
{
    if (!cameraObj.isOpened())
    {
       // qDebug() << "Cannot access the camera.\nProgram will not close down.";
       exit(EXIT_FAILURE);
    }

    if (fps == 60)
    {
        cameraObj.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        cameraObj.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    }
    else if (fps == 30)
    {
        cameraObj.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
        cameraObj.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    }

    cameraObj.set(cv::CAP_PROP_AUTOFOCUS, 1);

    cameraObj.set(cv::CAP_PROP_FOURCC, CV_FOURCC('M','J','P','G'));
    cameraObj.set(cv::CAP_PROP_FPS, fps);

    // Setting up the C922 to 1080p @ 30FPS.
    // camera.open(CV_CAP_DSHOW);
    // camera.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    // camera.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
    // camera.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
    // End
}

void Camera::setParam(VideoCapture &cameraObj, cv::VideoCaptureProperties property, unsigned char value)
{
    cameraObj.set(property, value);
}
