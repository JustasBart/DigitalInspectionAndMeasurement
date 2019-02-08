#include "measurements.h"

void Measurements::drawCalibrationLines(QPixmap *frameToDrawOn)
{
    QPainter painter(frameToDrawOn);

    painter.setBrush(QBrush(Qt::red));

    painter.setPen(QPen(Qt::black, 6, Qt::DashDotLine, Qt::RoundCap));
    painter.drawLine(10, 10, 10, frameToDrawOn->height() - 10);
}
