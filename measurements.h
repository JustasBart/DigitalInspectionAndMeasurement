#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include <QPixmap>
#include <QPainter>
#include "ui_mainwindow.h"

class Measurements
{
public:
    static void drawCalibrationLines(QPixmap *frameToDrawOn);
};

#endif // MEASUREMENTS_H
