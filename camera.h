#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/utils/trace.hpp>

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
    Mat retrieveGlobalUndistortedFrame(int width);
    void releaseCamera();

    static void process_frame(const cv::UMat& frame);

private:
    QImage Mat2QImage(cv::Mat const &src);
    VideoCapture *_cameraObj;
    Mat _currentFrameMat;
    Mat _currentFrameMatAdjustedColor;
    Mat _correctedMat;

    const Mat _cameraMatrix = (Mat1d(3, 3) << 6.8489708657322979e+002, 0, 320, 0, 6.8489708657322979e+002, 240, 0, 0, 1);
    const Mat _distortionCoefficients = (Mat1d(1, 5) << 4.4810908038479452e-002, 1.9604429778338306e-001, 0, 0, -7.0203187403062794e-001);

    // Tracking variables //
    Rect2d _roi;

};

#endif // CAMERA_H
