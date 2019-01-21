#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Defines
#define FPS 30

// OpenCV main image processing includes //
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// OpenCV label to Mat additional function includes //
#include "Qt-OpenCV-AdditionalLibrary.h"

// General QT includes:
#include <QTimer>
#include <QString>

// General functions
#include "settingshandler.h"
#include "algorithms.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void captureImage();
    void on_contrastSpinBox_valueChanged(int arg1);
    void on_brightnesspinBox_valueChanged(int arg1);
    void on_saturationSpinBox_valueChanged(int arg1);
    void on_zoomSpinBox_valueChanged(int arg1);
    void on_focusButton_pressed();
    void on_focusSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    // Variables //
    QTimer videoFPSTimer;
    Settings projectSettings;

    //_- Live Feed
    cv::Mat currentFrameMat;
    QPixmap currentFramePixmap;

    // Functions //

};

#endif // MAINWINDOW_H
