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

// General functions //
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
    void receiveData(unsigned int val, QString param);

private slots:
    void captureImage();

//    void on_contrastSpinBox_valueChanged(int arg1);
//    void on_brightnesspinBox_valueChanged(int arg1);
//    void on_saturationSpinBox_valueChanged(int arg1);
//    void on_zoomSpinBox_valueChanged(int arg1);
//    void on_focusButton_pressed();
//    void on_focusSpinBox_valueChanged(int arg1);

    void on_actionFull_screen_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    StartupDialog *_startUpDialog;
    QScreen *_screen;
    QRect _screenGeometry;

    void resizeWindowToResolution();
    void centerWindow();
    void loadGUISettings();
    void saveGUISettings();

    QTimer _videoFPSTimer;
    Camera _camObj;
    Options _usrOptions;

    unsigned int _camPort;
    bool _savePreferences;
    bool _fullScreen;
    unsigned int _res_Width;
    unsigned int _res_Height;
    unsigned int _fps;
};

#endif // MAINWINDOW_H
