#ifndef MEASURINGINTERFACE_H
#define MEASURINGINTERFACE_H

// QtIncludes //
#include <QMouseEvent>
#include <QFileDialog>
#include <QTableView>
#include <QPainter>
#include <QDialog>
#include <QDebug>
#include <QPoint>
#include <QRect>

// Local includes //
#include "helperclass.h"
#include "linesclass.h"

// OpenCV includes //
#include <opencv2/core/utility.hpp>
#include "opencv2/features2d.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core.hpp"

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
    void receiveCurrentMat(Mat currentFrame, QSize frameRes, QRect screenSize);
    void labelMousePos(QPoint &pos);
    void labelMouseClickedPos(QPoint &pos);

public: signals:
    void sendTableObject(QTableView &listView);

private slots:
    void on_saveImageButton_pressed();
    void on_drawGridCheckbox_stateChanged(int arg1);
    void on_gridSlider_sliderMoved(int position);
    void on_drawScaleButton_pressed();
    void on_removeScaleButton_pressed();
    void on_mmSpinbox_valueChanged(int arg1);
    void on_smallGridSlider_sliderMoved(int position);
    void on_drawRulerButton_pressed();

private:
    Ui::MeasuringInterface *ui;

    QPixmap matToPixmap(Mat frame);
    void resizeWindowToScreenSize();
    void resizeLabelToWindow();
    void updateFrame(Mat newFrame);
    void drawLine();
    void clickedLabel(QMouseEvent *event);
    void updateGridSizeLabel(int val);

    LinesClass *_lClassObj;

    Mat _workingFrame;
    Mat _frameWithGrid;
    Mat _frameWithScale;
    Mat _frameWithRulers;

    bool _rulerDrawingStatus;
    bool _scaleDrawingStatus;
    QPoint _tempPoint1;
    QPoint _tempPoint2;

    QPixmap _workingPixmap;
    int _screenWidth;
    int _screenHeight;
    int _frameWidth;
    int _frameHeight;

    double _PXtoMM;

    QPoint _mappedPoint1;
    QPoint _mappedPoint2;
};

#endif // MEASURINGINTERFACE_H
