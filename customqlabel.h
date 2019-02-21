#ifndef CUSTOMQLABEL_H
#define CUSTOMQLABEL_H

// QtIncludes //
#include <QMouseEvent>
#include <QObject>
#include <QWidget>
#include <QLabel>

class CustomQLabel : public QLabel
{
    Q_OBJECT

public:
    CustomQLabel(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void sendMousePosition(QPoint &);
    void sendMousePoint(QPoint &);
};

#endif // CUSTOMQLABEL_H
