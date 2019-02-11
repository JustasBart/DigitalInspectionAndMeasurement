#ifndef MEASURINGINTERFACE_H
#define MEASURINGINTERFACE_H

#include <QDialog>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QDebug>

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
    void receiveCurrentMat(Mat currentFrame, QRect screenSize);

private:
    Ui::MeasuringInterface *ui;

    QPixmap matToPixmap(Mat frame);
    void resizeWindowToScreenSize();
    void resizeLabelToWindow();

    Mat _workingFrame;
    QPixmap _workingPixmap;
    int _screenWidth;
    int _screenHeight;
};

#endif // MEASURINGINTERFACE_H
