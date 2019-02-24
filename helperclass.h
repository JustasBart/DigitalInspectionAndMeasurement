#ifndef HELPERCLASS_H
#define HELPERCLASS_H

// OpenCV includes //
#include <opencv2/core/utility.hpp>
#include "opencv2/features2d.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

class HelperClass
{
public:
    static void placeGrid(Mat &frame, int distance);
    static int map(const int x, const int in_min, const int in_max, const int out_min, const int out_max);
};

#endif // HELPERCLASS_H
