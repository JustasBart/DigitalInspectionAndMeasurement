#include "linesclass.h"

Ruler::Ruler(QPoint p1, QPoint p2)
{
    _point1 = p1;
    _point2 = p2;
}

void Ruler::drawRuler(Mat &frameMat, int rulerEnumerator)
{
    cv::line(frameMat, cv::Point2d(_point1.x(), _point1.y()), cv::Point2d(_point2.x(), _point2.y()), cv::Scalar((rulerEnumerator * 5) + 100, (rulerEnumerator * 10) + 55, (rulerEnumerator * 5)), 3);

    cv::circle(frameMat, cv::Point2d(_point1.x(), _point1.y()), 8, Scalar(0, 0, 255), 1);
    cv::circle(frameMat, cv::Point2d(_point2.x(), _point2.y()), 8, Scalar(0, 0, 255), 1);

    cv::Point midPoint;
    midPoint.x = ((_point1.x() + _point2.x()) / 2);
    midPoint.y = ((_point1.y() + _point2.y()) / 2);

    cv::putText(frameMat, "Ruler " + QString::number(rulerEnumerator).toStdString(), midPoint, 5, 1, Scalar(255, 255, 255));
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
    _lineGuard = false;
    _currentState = 0;
    _tableHeader << "Ruler";
}

double LinesClass::calculatePXtoMM(const QPoint p1, const QPoint p2, int distance)
{
    double lineLenght = calculateLenghtOfLine(p1, p2);
    return lineLenght / distance;
}

void LinesClass::addRuler(Mat &drawingMat, QPoint _tempPoint1, QPoint _tempPoint2, QSize frameSize, QSize matSize, double pxToMMRatio)
{
    _PXtoMM = pxToMMRatio;

    _scaledPoint1.setX( HelperClass::map(_tempPoint1.x(), 0, frameSize.width(), 0, matSize.width()) );
    _scaledPoint1.setY( HelperClass::map(_tempPoint1.y(), 0, frameSize.height(), 0, matSize.height()) );

    _scaledPoint2.setX( HelperClass::map(_tempPoint2.x(), 0, frameSize.width(), 0, matSize.width()) );
    _scaledPoint2.setY( HelperClass::map(_tempPoint2.y(), 0, frameSize.height(), 0, matSize.height()) );

    Ruler tempRuler = *new Ruler(_scaledPoint1, _scaledPoint2);

    _rulersList.push_back(tempRuler);

    qDebug() << "Added a new ruler";

    for (int i = 0; i < _rulersList.count(); i++)
    {
        _rulersList[i].drawRuler(drawingMat, i+1);
    }
}

void LinesClass::receiveTableObject(QTableView &tableView)
{
    QStandardItemModel *model = new QStandardItemModel();
    QList<QStandardItem> items;

    double lineLength = 0;

    model->clear();
    for (int i = 0; i < _rulersList.count(); i++)
    {
        QString text = QString::number(i);

        lineLength = calculateLenghtOfLine(_rulersList[i].getFirstPoint(), _rulersList[i].getSecondPoint());
        qDebug() << "P1 " << _rulersList[i].getFirstPoint() << " P2 " << _rulersList[i].getSecondPoint() << " Length " << lineLength;

        QStandardItem *item = new QStandardItem("Ruler " + QString::number(i+1) + " " + QString::number(lineLength / _PXtoMM) + "mm");

        model->appendRow(item);
    }

    model->setHorizontalHeaderLabels(_tableHeader);

    tableView.setShowGrid(true);
    tableView.setModel(model);
}

double LinesClass::calculateLenghtOfLine(const QPoint p1, const QPoint p2)
{
    return qSqrt( qPow(p1.x() - p2.x(), 2) +  qPow(p1.y() - p2.y(), 2)  );
}
