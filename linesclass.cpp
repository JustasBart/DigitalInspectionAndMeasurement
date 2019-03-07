#include "linesclass.h"

Ruler::Ruler(QPoint p1, QPoint p2)
{
    _point1 = p1;
    _point2 = p2;
}

void Ruler::drawRuler(Mat &frameMat)
{
    cv::line(frameMat, cv::Point2d(_point1.x(), _point1.y()), cv::Point2d(_point2.x(), _point2.y()), cv::Scalar(255, 255, 0));
}

QPoint Ruler::getFirstPoint()
{
    return _point1;
}

QPoint Ruler::getSecondPoint()
{
    return _point2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief LinesClass::LinesClass
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LinesClass::LinesClass()
{
    _PXtoMM = 0.0;
    _lineGuard = false;
    _currentState = 0;

    _tableHeader << "Ruler";
}

double LinesClass::calculatePXtoMM(const QPoint p1, const QPoint p2, int distance)
{
    return qSqrt( qPow(p1.x() - p2.x(), 2) + qPow(p1.y() - p2.y(), 2) ) / distance;
}

void LinesClass::addRuler(Mat &drawingMat, QPoint _tempPoint1, QPoint _tempPoint2, QSize frameSize, QSize matSize)
{
    _scaledPoint1.setX( HelperClass::map(_tempPoint1.x(), 0, frameSize.width(), 0, matSize.width()) );
    _scaledPoint1.setY( HelperClass::map(_tempPoint1.y(), 0, frameSize.height(), 0, matSize.height()) );

    _scaledPoint2.setX( HelperClass::map(_tempPoint2.x(), 0, frameSize.width(), 0, matSize.width()) );
    _scaledPoint2.setY( HelperClass::map(_tempPoint2.y(), 0, frameSize.height(), 0, matSize.height()) );

    Ruler tempRuler = *new Ruler(_scaledPoint1, _scaledPoint2);

    _rulersList.push_back(tempRuler);

    qDebug() << "Added a new ruler";

    for (int i = 0; i < _rulersList.count(); i++)
    {
        _rulersList[i].drawRuler(drawingMat);
    }
}

void LinesClass::receiveTableObject(QTableView &tableView)
{
    QStandardItemModel *model = new QStandardItemModel();
    QList<QStandardItem> items;

    model->clear();
    for (int i = 0; i < _rulersList.count(); i++)
    {
        QString text = QString::number(i);

        QStandardItem *item = new QStandardItem("Ruler " + QString::number(i));

        model->appendRow(item);
    }

    model->setHorizontalHeaderLabels(_tableHeader);

    tableView.setShowGrid(true);
    tableView.setModel(model);
}

double LinesClass::calculateLenghtOfLine(const QPoint p1, const QPoint p2)
{
    return qSqrt( qPow(p2.x() - p1.x(), 2) +  qPow(p2.y() - p1.y(), 2)  );
}
