#include "helperclass.h"

HelperClass::HelperClass()
{

}

int HelperClass::map(const int x, const int in_min, const int in_max, const int out_min, const int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void HelperClass::placeGrid(Mat &frame, int distance)
{
    int width  = frame.size().width;
    int height = frame.size().height;

    for(int i = 0; i < height; i += distance)
      cv::line(frame, Point(0, i), Point(width, i), cv::Scalar(255, 255, 255));
    for(int i = 0; i < width; i += distance)
        cv::line(frame, Point(i, 0), Point(i, height), cv::Scalar(255, 255, 255));
}
