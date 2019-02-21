#include "customqlabel.h"

CustomQLabel::CustomQLabel(QWidget *parent) : QLabel (parent)
{
    this->setMouseTracking(true);
}

void CustomQLabel::mouseMoveEvent(QMouseEvent *event)
{
    QPoint mousePosition = event->pos();

    if (mousePosition.x() <= this->size().width() && mousePosition.y() <= this->size().height())
    {
        if (mousePosition.x() >= 0 && mousePosition.y() >= 0)
        {
            emit sendMousePosition(mousePosition);
        }
    }
}

void CustomQLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint mousePosition = event->pos();
        emit sendMousePoint(mousePosition);
    }
}
