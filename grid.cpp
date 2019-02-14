#include "grid.h"

void Grid::placeGrid(Mat &frame, int distance)
{
    int width  = frame.size().width;
    int height = frame.size().height;

    for(int i = 0; i < height; i += distance)
      cv::line(frame, Point(0, i), Point(width, i), cv::Scalar(255, 255, 255));

    for(int i = 0; i < width; i += distance)
      cv::line(frame, Point(i, 0), Point(i, height), cv::Scalar(255, 255, 255));

//    for(int i = 0;i < width; i += distance)
//      for(int j = 0; j < height; j += distance)
//        frame.at<Vec3b>(i, j) = cv::Scalar(10, 10, 10);
}
