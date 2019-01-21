#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "QtDebug"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Algorithms
{
public:
    static void sayHello();

private:
    Mat PictureMat;
};

#endif // ALGORITHMS_H
