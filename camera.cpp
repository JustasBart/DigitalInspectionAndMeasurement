#include "camera.h"

int Camera::cameraInit(const int camera, const int fps, const int &width, const int &height)
{
    _cameraObj = new VideoCapture(camera);

    if (!_cameraObj -> isOpened())
    {
       Errors::cameraOpenErrorWindow();
       return -1;
    }

    qDebug() << "Setting frame W: " << width;
    qDebug() << "Setting frame H: " << height;

    setParam(CAP_PROP_FRAME_WIDTH, width);
    setParam(CAP_PROP_FRAME_HEIGHT, height);

    setParam(CAP_PROP_AUTOFOCUS, 1);

    setParam(CAP_PROP_FOURCC, static_cast<unsigned char>(CV_FOURCC('M','J','P','G')));
    setParam(CAP_PROP_FPS, fps);

    // Setting up the C922 to 1080p @ 30FPS.
    // camera.open(CV_CAP_DSHOW);
    // camera.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    // camera.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
    // camera.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
    // End

    return 0;
}

void Camera::setParam(cv::VideoCaptureProperties param, int value)
{
    _cameraObj -> set(param, value);
}

unsigned char Camera::getParam(VideoCaptureProperties param)
{
    return static_cast<unsigned char>(_cameraObj -> get(param));
}

QPixmap Camera::captureImage()
{
    *_cameraObj >> _currentFrameMat;

    cv::cvtColor(_currentFrameMat, _currentFrameMat, CV_BGR2RGB);
    QImage dest(static_cast<const uchar *>(_currentFrameMat.data), _currentFrameMat.cols, _currentFrameMat.rows, static_cast<int>(_currentFrameMat.step), QImage::Format_RGB888);
    dest.bits();

    return QPixmap::fromImage(dest);
}

unsigned char Camera::getFPS()
{
    return getParam(CAP_PROP_FPS);
}

void Camera::setBufferSize(int frames)
{
    _cameraObj -> set(CV_CAP_PROP_BUFFERSIZE, frames);
}

Mat Camera::retrieveGlobalFrame()
{
    return _currentFrameMat;
}
