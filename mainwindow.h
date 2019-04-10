#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Defines //
#define GROUP_LOCATION     "GUISettings"

#define ARDUINO_VENDOR_ID  "2341"
#define ARDUINO_PRODUCT_ID "8037"

// OpenCV main image processing includes //
#include <opencv2/highgui.hpp>

// General QT includes //
#include <QGuiApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QVariant>
#include <QPainter>
#include <QString>
#include <QScreen>
#include <QTimer>
#include <QStyle>

// General functions //
#include "measuringinterface.h"
#include "startupdialog.h"
#include "usersettings.h"
#include "serialcomms.h"
#include "camera.h"
#include "errors.h"

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
    void sendGlobalMat(Mat currentFrame, QSize frameRes, QRect screenSize);

private slots:
    void captureImage();
    void on_focusButton_pressed();
    void on_actionFull_screen_triggered(bool checked);
    void on_actionCenter_window_triggered();
    void on_actionSet_to_defaults_triggered();
    void on_modeButton_pressed();
    void on_positionCalibrationButton_pressed();

    void on_focusSlider_sliderMoved(int position);
    void on_zoomSlider_sliderMoved(int position);
    void on_saturationSlider_sliderMoved(int position);
    void on_brightnessSlider_sliderMoved(int position);
    void on_contrastSlider_sliderMoved(int position);

    void on_contrastOptionsBtn_pressed();
    void on_brightnessOptionsBtn_pressed();
    void on_saturationOptionsBtn_pressed();
    void on_zoomOptionsBtn_pressed();
    void on_focusOptionsBtn_pressed();
    void on_captureButton_pressed();
    void on_measureButton_pressed();
    void on_distortionButton_pressed();

    void on_lensCorrectioncheckBox_stateChanged(int arg1);
    void on_actionEnumerate_Ports_triggered();
    void on_actionAttempt_to_connect_triggered();

    void setRingLighGUI(bool state);
    void on_actionCheck_connection_status_triggered();
    void on_LightLevelSlider_sliderMoved(int position);

    void on_gantryUpButton_pressed();

    void on_gantryDownButton_pressed();

    void on_gantryLeftButton_pressed();

    void on_gantryRightButton_pressed();

private:
    Ui::MainWindow *ui;
    StartupDialog *_startUpDialog;
    MeasuringInterface *_measuringInterface;
    QScreen *_screen;
    QRect _screenGeometry;

    void resizeWindowToScreenSize();
    void resizeLabelToWindow();
    void centerWindow();
    void loadGUISettings();
    void saveGUISettings();
    void defaultCamOpt();
    void defaultUIVals();
    void setOptionsButtons(bool val);
    void setMeasurementButtons(bool val);
    void drawCalibrationLines(QPixmap *frameToDrawOn);
    void listenToKeyPress(QKeyEvent *event);
    void switchAlgToGantry(bool state);

    QTimer _videoFPSTimer;

    SerialComms _ardSerial;
    Camera _camObj;
    Options _usrOptions;

    Mat _globalFrame;
    QPixmap _globalQPixmap;

    int _camPort;
    bool _savePreferences;
    bool _fullScreen;
    int _res_Width;
    int _res_Height;
    int _fps;

    bool _calibrationInProgress;
    bool _liveLensCorrection;
};

#endif // MAINWINDOW_H
