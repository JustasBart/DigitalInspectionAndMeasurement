#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Defines
#define FPS 30
#define CAMERA_HARDWARE 0

// OpenCV main image processing includes //
#include <opencv2/highgui/highgui.hpp>

// General QT includes:
#include <QTimer>
#include <QString>

// General functions
#include "algorithms.h"
#include "camera.h"
#include "errors.h"
#include "options.h"
#include "usersettings.h"

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

    void init();

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

    QTimer _videoFPSTimer;
    Camera camObj;
    Options usrOptions;
};

#endif // MAINWINDOW_H
