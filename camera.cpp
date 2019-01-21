#include "camera.h"

void Camera::cameraInit(unsigned char camera, unsigned char fps)
{
    _cameraObj = new VideoCapture(camera);

    if (!_cameraObj -> isOpened())
    {
       exit(EXIT_FAILURE);
    }

    if (fps == 60)
    {
        setParam(CAP_PROP_FRAME_WIDTH, 640);
        setParam(CAP_PROP_FRAME_HEIGHT, 480);
    }
    else if (fps == 30)
    {
        setParam(CAP_PROP_FRAME_WIDTH, 1280);
        setParam(CAP_PROP_FRAME_HEIGHT, 720);
    }

    setParam(CAP_PROP_AUTOFOCUS, 1);

    setParam(CAP_PROP_FOURCC, CV_FOURCC('M','J','P','G'));
    setParam(CAP_PROP_FPS, fps);

    // Setting up the C922 to 1080p @ 30FPS.
    // camera.open(CV_CAP_DSHOW);
    // camera.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    // camera.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
    // camera.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
    // End
}

void Camera::setParam(cv::VideoCaptureProperties param, unsigned char value)
{
    _cameraObj -> set(param, value);
}

unsigned char Camera::getParam(VideoCaptureProperties param)
{
    return _cameraObj -> get(param);
}

QPixmap Camera::captureImage()
{
    *_cameraObj >> _currentFrameMat;
    return MatToQPixmap( _currentFrameMat );
}

unsigned char Camera::getFPS()
{
    return getParam(CAP_PROP_FPS);
}
