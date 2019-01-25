#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Defines //
#define GROUP_LOCATION  "GUISettings"

// OpenCV main image processing includes //
#include <opencv2/highgui/highgui.hpp>

// General QT includes //
#include <QTimer>
#include <QString>
#include <QVariant>
#include <QStyle>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QScreen>

#include <QPainter>

// General functions //
#include "startupdialog.h"
#include "camera.h"
#include "algorithms.h"
#include "errors.h"
#include "options.h"
#include "usersettings.h"
#include "measurements.h"

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
    void receiveData(unsigned int val, QString param);

public: signals:
    void sendOffsets(unsigned int arg, int val);

private slots:
    void captureImage();
    void on_contrastSpinBox_valueChanged(int arg1);
    void on_brightnesSpinBox_valueChanged(int arg1);
    void on_saturationSpinBox_valueChanged(int arg1);
    void on_zoomSpinBox_valueChanged(int arg1);
    void on_focusButton_pressed();
    void on_focusSpinBox_valueChanged(int arg1);
    void on_actionFull_screen_triggered(bool checked);
    void on_actionCenter_window_triggered();
    void on_actionSet_to_defaults_triggered();
    void on_modeButton_clicked();
    void on_positionCalibrationButton_clicked();
    void on_streamingButton_clicked();

private:
    Ui::MainWindow *ui;
    StartupDialog *_startUpDialog;
    QScreen *_screen;
    QRect _screenGeometry;

    void resizeWindowToScreenSize();
    void resizeLabelToWindow();
    void centerWindow();
    void loadGUISettings();
    void saveGUISettings();
    void defaultCamOpt();
    void defaultUIVals();
    void setMeasurementButtons(bool val);

    QTimer _videoFPSTimer;
    Camera _camObj;
    Options _usrOptions;
    QPixmap _globalFrame;

    int _camPort;
    bool _savePreferences;
    bool _fullScreen;
    int _res_Width;
    int _res_Height;
    int _fps;

    bool _calibrationInProgress;
};

#endif // MAINWINDOW_H
