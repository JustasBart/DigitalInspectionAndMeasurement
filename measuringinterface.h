#ifndef MEASURINGINTERFACE_H
#define MEASURINGINTERFACE_H

#include <QDialog>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

namespace Ui
{
    class MeasuringInterface;
}

class MeasuringInterface : public QDialog
{
    Q_OBJECT

public:
    explicit MeasuringInterface(QWidget *parent = nullptr);
    ~MeasuringInterface();

public slots:
    void receiveCurrentMat(Mat currentFrame);

private:
    Ui::MeasuringInterface *ui;

    Mat _workingFrame;
};

#endif // MEASURINGINTERFACE_H
