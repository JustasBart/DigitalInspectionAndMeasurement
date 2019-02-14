#include "measurements.h"

void Measurements::drawCalibrationLines(QPixmap *frameToDrawOn)
{
    QPainter painter(frameToDrawOn);

    int width = frameToDrawOn->width();
    int height = frameToDrawOn->height();

    int lineThickness = static_cast<int>( frameToDrawOn->width() * 0.0045 );
    int offset = static_cast<int>( frameToDrawOn->width() * 0.02 );

    painter.setPen(QPen( Qt::red, lineThickness, Qt::DashLine, Qt::RoundCap) );

    for (int i = 1; i <= 4; i++)
    {
        painter.drawLine(offset*i, offset*i, offset*i, height - offset*i);
        painter.drawLine(width - offset*i, offset*i, width - offset*i, height - offset*i);
    }

    painter.setPen(QPen( Qt::blue, lineThickness - 2, Qt::SolidLine, Qt::RoundCap) );

    painter.drawLine(offset + 5, offset, width - offset,  height - offset - 5);
    painter.drawLine(width - offset - 5, offset, offset + 2, height - offset - 5);

    painter.drawLine(width/2, height/2 + offset*10, width/2, height/2 - offset*10);

    painter.setPen(QPen( Qt::green, lineThickness - 2, Qt::SolidLine, Qt::RoundCap) );

    painter.drawLine(width/2 - offset*6, height/2 - offset*10, width/2 + offset*6, height/2 - offset*10);
    painter.drawLine(width/2 - offset*6, height/2 + offset*10, width/2 + offset*6, height/2 + offset*10);

    painter.setPen(QPen( Qt::yellow, lineThickness - 2, Qt::SolidLine, Qt::RoundCap) );

    painter.drawLine(offset*5, height/2, width/2 - offset*2, height/2);
    painter.drawLine(width - offset*5, height/2, width/2 + offset*2, height/2);
}
