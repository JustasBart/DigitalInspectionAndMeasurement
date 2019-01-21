#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "QtDebug"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Algorithms
{
public:
    static void sayHello();
private:
    Mat PictureMat;
};

#endif // ALGORITHMS_H
