#-------------------------------------------------
#
# Project created by QtCreator 2018-11-06T10:09:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DigitalInspectionAndMeasurement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    algorithms.cpp \
    camera.cpp \
    errors.cpp \
    usersettings.cpp \
    startupdialog.cpp \
    measurements.cpp \
    measuringinterface.cpp \
    measuringinterface_events.cpp \
    measuringinterface_functions.cpp \
    main_events.cpp \
    main_functions.cpp \
    measurements_events.cpp \
    grid.cpp

HEADERS += \
        mainwindow.h \
    algorithms.h \
    camera.h \
    errors.h \
    usersettings.h \
    options.h \
    startupdialog.h \
    measurements.h \
    measuringinterface.h \
    measuringinterface_functions.h \
    grid.h

FORMS += \
        mainwindow.ui \
    startupdialog.ui \
    measuringinterface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#
# OPENCV >___
#

INCLUDEPATH += C:\\opencv\\release\\install\\include

LIBS += -LC:\\opencv\\release\\bin \
    libopencv_core343 \
    libopencv_highgui343 \
    libopencv_imgproc343 \
    libopencv_features2d343 \
    libopencv_calib3d343 \
    libopencv_video343 \
    libopencv_videoio343 \
    libopencv_imgcodecs343 \
    libopencv_objdetect343 \
