#ifndef GRID_H
#define GRID_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class Grid
{
public:
    static void placeGrid(Mat &frame, int distance);
};

#endif // GRID_H
