#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/utils/trace.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/calib3d/calib3d.hpp"

#include <limits>
#include <numeric>

#include <QDebug>
#include <QString>
#include "errors.h"

using namespace cv;
using namespace std;

class Camera
{
public:
    int cameraInit(const int camera, const int fps, const int &width, const int &height);
    void setParam(VideoCaptureProperties param, int value);
    unsigned char getParam(cv::VideoCaptureProperties param);
    void setBufferSize(int frames);
    Mat captureFrameMat();
    QPixmap convertMatToQPixmap(Mat &frameToConver);
    unsigned char getFPS();
    Mat retrieveGlobalFrame();
    Mat retrieveGlobalUndistortedFrame(int width);
    void releaseCamera();

private:
    QImage Mat2QImage(cv::Mat const &src);
    VideoCapture *_cameraObj;
    Mat _currentFrameMat;
    Mat _currentFrameMatAdjustedColor;
    Mat _correctedMat;

    const Mat _cameraMatrix = (Mat1d(3, 3) << 6.5178005743280778e+002, 0, 320, 0, 6.5178005743280778e+002, 240, 0, 0, 1);
    const Mat _distortionCoefficients = (Mat1d(1, 5) << 4.8696914178490348e-002, -7.3927152959877243e-002, 0, 0, -1.9647143782874946e-001);

    // Tracking variables //
    Rect2d _roi;
};

#endif // CAMERA_H
