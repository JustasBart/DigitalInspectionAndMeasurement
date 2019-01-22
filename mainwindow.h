#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Defines
#define FPS             30
#define CAMERA_HARDWARE 0
#define GROUP_LOCATION  "GUISettings"

// OpenCV main image processing includes //
#include <opencv2/highgui/highgui.hpp>

// General QT includes:
#include <QTimer>
#include <QString>
#include <QVariant>
#include <QStyle>
#include <QDesktopWidget>

// General functions
#include "startupdialog.h"
#include "camera.h"
#include "algorithms.h"
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

public slots:
    void receiveData(QString param);

private slots:
    // void captureImage();

//    void on_contrastSpinBox_valueChanged(int arg1);
//    void on_brightnesspinBox_valueChanged(int arg1);
//    void on_saturationSpinBox_valueChanged(int arg1);
//    void on_zoomSpinBox_valueChanged(int arg1);
//    void on_focusButton_pressed();
//    void on_focusSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    StartupDialog *startUpDialog;

    void centerWindow();
    void loadGUISettings();
    void saveGUISettings();

    QTimer _videoFPSTimer;
    Camera _camObj;
    Options _usrOptions;

    static unsigned int _res_Width;
    static unsigned int _res_Height;
    static unsigned char _fps;
};

#endif // MAINWINDOW_H
