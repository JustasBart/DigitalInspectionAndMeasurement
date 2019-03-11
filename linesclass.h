#ifndef LINESCLASS_H
#define LINESCLASS_H

// QtIncludes //
#include <QStandardItemModel>
#include <QModelIndex>
#include <QHeaderView>
#include <QTableView>
#include <QObject>
#include <QPoint>
#include <QtMath>
#include <QLabel>
#include <QDebug>
#include <QList>
#include <QDate>

// Generic includes //
#include <helperclass.h>
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <vector>

// OpenCV includes //
#include <opencv2/imgproc.hpp>
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

class Ruler
{
public:
    Ruler(QPoint p1, QPoint p2);
    void drawRuler(Mat &frameMat, int rulerEnumerator);
    QPoint getFirstPoint();
    QPoint getSecondPoint();
    cv::Scalar getColorAtIndex(int index);

private:
    QPoint _point1;
    QPoint _point2;

    QList<Scalar> _rulerColors;
};

class LinesClass : public QObject
{
    Q_OBJECT

public:
    LinesClass();

    void addRuler(Mat &drawingMat, QPoint _tempPoint1, QPoint _tempPoint2, QSize frameSize, QSize matSize, double pxToMMRatio);
    void reDrawRulers(Mat &frameMat);
    static double calculatePXtoMM(const QPoint p1, const QPoint p2, int distance);
    static double calculateLenghtOfLine(const QPoint p1, const QPoint p2);
    void setNewPxToMM(double pixToMMRatio);
    int countRulers();

public slots:
    void receiveTableObject(QTableView &tableView);
    void removeRuler(int rowIndex);
    void removeRulers();
    void addTableRulerText(Mat *frameToDrawOn);

private:
    double _PXtoMM;
    QList <Ruler> _rulersList;

    bool _lineGuard;
    int _currentState;

    QPoint _tempPoint1;
    QPoint _tempPoint2;

    QPoint _scaledPoint1;
    QPoint _scaledPoint2;

    QStringList _tableHeader;
    QStandardItemModel *_tableModel;
    QList<QStandardItem> _items;
};

#endif // LINESCLASS_H
