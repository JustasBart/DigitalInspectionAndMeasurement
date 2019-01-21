#ifndef QTOPENCVLIB_H
#define QTOPENCVLIB_H

#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QPixmap>

using namespace cv;
using namespace std;

QPixmap MatToQPixmap(const Mat&);

typedef cv::Mat SignalMat;

#endif
