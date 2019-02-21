#ifndef DYNAMICLINE_H
#define DYNAMICLINE_H

#include <QPainter>
#include <QWidget>
#include <QPixmap>

class DynamicLine
{
public:
    DynamicLine();

    QPixmap drawLine( QPixmap &drawingMap );

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void on_btnLine_clicked();
    void on_btnRect_clicked();

private:
    QPainter _painter;
    QPixmap _mPix;
    QLine _mLine;
    QRect _mRect;

    bool _mousePressed;
    bool _drawStarted;
};

#endif
