#include "dynamicline.h"

#include <QMouseEvent>
#include <QPainter>

DynamicLine::DynamicLine() :
    _mousePressed(false),
    _drawStarted(false)
{ }

void DynamicLine::mousePressEvent(QMouseEvent* event)
{
    _mousePressed = true;

    _mLine.setP1(event->pos());
    _mLine.setP2(event->pos());
}

void DynamicLine::mouseMoveEvent(QMouseEvent* event)
{
    if(event->type() == QEvent::MouseMove)
    {
        _mLine.setP2(event->pos());
    }
}

void DynamicLine::mouseReleaseEvent(QMouseEvent *event)
{
    _mousePressed = false;
}

void DynamicLine::paintEvent(QPaintEvent *event)
{
    if(_mousePressed)
    {
        _painter.drawPixmap(0, 0, _mPix);

        _painter.drawLine(_mLine);

        _drawStarted = true;
    }
    else if (_drawStarted)
    {
        QPainter tempPainter(&_mPix);

        tempPainter.drawLine(_mLine);

        _painter.drawPixmap(0, 0, _mPix);
    }

    _painter.end();
}
