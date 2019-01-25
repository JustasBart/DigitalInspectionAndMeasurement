#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include <QPixmap>
#include <QPainter>
#include "ui_mainwindow.h"

class Measurements
{
public:
    static void drawCalibrationLines(QPixmap *frameToDrawOn);

public slots:
    void receiveVals(unsigned int val, QString param);

private:
    int _horizontalOffset;
    int _vertocalOffset;
};

#endif // MEASUREMENTS_H
