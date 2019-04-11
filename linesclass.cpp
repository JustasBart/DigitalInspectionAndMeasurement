#include "linesclass.h"

Ruler::Ruler(QPoint p1, QPoint p2)
{
    _point1 = p1;
    _point2 = p2;

    _rulerColors.push_back( Scalar(0, 100, 255)   ); // Ruler 1
    _rulerColors.push_back( Scalar(0, 195, 255)   ); // Ruler 2
    _rulerColors.push_back( Scalar(0, 255, 230)   ); // Ruler 3
    _rulerColors.push_back( Scalar(0, 255, 70)    ); // Ruler 4
    _rulerColors.push_back( Scalar(190, 255, 0)   ); // Ruler 5
    _rulerColors.push_back( Scalar(255, 225, 0)   ); // Ruler 6
    _rulerColors.push_back( Scalar(0, 106, 255)   ); // Ruler 7
    _rulerColors.push_back( Scalar(0, 55, 255)    ); // Ruler 8
    _rulerColors.push_back( Scalar(255, 38, 0)    ); // Ruler 9
    _rulerColors.push_back( Scalar(255, 0, 140)   ); // Ruler 10
    _rulerColors.push_back( Scalar(255, 0, 195)   ); // Ruler 11
    _rulerColors.push_back( Scalar(215, 0, 255)   ); // Ruler 12
    _rulerColors.push_back( Scalar(100, 0, 255)   ); // Ruler 13
    _rulerColors.push_back( Scalar(245, 255, 70)  ); // Ruler 14
    _rulerColors.push_back( Scalar(70, 255, 190)  ); // Ruler 15
    _rulerColors.push_back( Scalar(190, 112, 255) ); // Ruler 16
    _rulerColors.push_back( Scalar(250, 255, 110) ); // Ruler 17
    _rulerColors.push_back( Scalar(110, 200, 255) ); // Ruler 18
    _rulerColors.push_back( Scalar(110, 255, 160) ); // Ruler 19
    _rulerColors.push_back( Scalar(255, 157, 90)  ); // Ruler 20
}

void Ruler::drawRuler(Mat &frameMat, int rulerEnumerator)
{
    cv::line(frameMat, cv::Point2d(_point1.x(), _point1.y()), cv::Point2d(_point2.x(), _point2.y()), _rulerColors[rulerEnumerator-1], 1);

    cv::circle(frameMat, cv::Point2d(_point1.x(), _point1.y()), 8, Scalar(0, 0, 255), 1);
    cv::circle(frameMat, cv::Point2d(_point2.x(), _point2.y()), 8, Scalar(0, 0, 255), 1);

    cv::Point midPoint;
    midPoint.x = ((_point1.x() + _point2.x()) / 2 - 45);
    midPoint.y = ((_point1.y() + _point2.y()) / 2);

    cv::putText(frameMat, "Ruler " + QString::number(rulerEnumerator).toStdString(), midPoint, 5, 1, Scalar(45, 255, 241));
}

QPoint Ruler::getFirstPoint()
{
    return _point1;
}

QPoint Ruler::getSecondPoint()
{
    return _point2;
}

cv::Scalar Ruler::getColorAtIndex(int index)
{
    return _rulerColors[index];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief LinesClass::LinesClass
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LinesClass::LinesClass()
{
    _lineGuard = false;
    _currentState = 0;
    _tableHeader << "Ruler";
    _tableModel = new QStandardItemModel();
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

    reDrawRulers(drawingMat);
}

void LinesClass::reDrawRulers(Mat &frameMat)
{
    for (int i = 0; i < _rulersList.count(); i++)
    {
        _rulersList[i].drawRuler(frameMat, i+1);
    }
}

void LinesClass::receiveTableObject(QTableView &tableView)
{
    double lineLength = 0;

    _tableModel->clear();

    for (int i = 0; i < _rulersList.count(); i++)
    {
        QString text = QString::number(i);

        lineLength = calculateLenghtOfLine(_rulersList[i].getFirstPoint(), _rulersList[i].getSecondPoint());

        // qDebug() << "P1 " << _rulersList[i].getFirstPoint() << " P2 " << _rulersList[i].getSecondPoint() << " Length " << lineLength;

        QStandardItem *item = new QStandardItem("Ruler " + QString::number(i+1) + " Length: " + QString::number(lineLength / _PXtoMM) + "mm");

        _tableModel->appendRow(item);
    }

    _tableModel->setHorizontalHeaderLabels(_tableHeader);

    tableView.setShowGrid(true);
    tableView.setModel(_tableModel);

    tableView.setColumnWidth(0, 190);
}

double LinesClass::calculateLenghtOfLine(const QPoint p1, const QPoint p2)
{
    return qSqrt( qPow(p1.x() - p2.x(), 2) +  qPow(p1.y() - p2.y(), 2) );
}

void LinesClass::removeRuler(int rowIndex)
{
    if (rowIndex >= 0)
    {
        _rulersList.removeAt(rowIndex);
        qDebug() << "Ruler at the index of [" << rowIndex << "] was removed.";
    }
    else
    {
        qDebug() << "Error the ruler was not found and could not be removed!";
    }
}

void LinesClass::removeRulers()
{
    _rulersList.clear();
}

void LinesClass::setNewPxToMM(double pixToMMRatio)
{
    _PXtoMM = pixToMMRatio;
}

void LinesClass::addTableRulerText(Mat *frameToDrawOn)
{
    int row = _tableModel->rowCount();
    int col = _tableModel->columnCount();

    double lineLength = 0;
    QVariant content;

    for (int i = 0; i < row ; ++i)
    {
        for (int j = 0; j < col; j++)
        {
            content = _tableModel->data(_tableModel->index(i, j), Qt::DisplayRole);
            lineLength = calculateLenghtOfLine(_rulersList[i].getFirstPoint(), _rulersList[i].getSecondPoint());

            cv::putText(*frameToDrawOn, "Ruler " + QString::number(i+1).toStdString() + " Lenght: " +
                        QString::number(lineLength / _PXtoMM).toStdString() + "mm",
                        cv::Point2d(frameToDrawOn->cols - 370, (i * 30) + 50),5, 1, _rulersList[0].getColorAtIndex(i));
        }
    }

    cv::putText(*frameToDrawOn, "Date saved: " + QDate::currentDate().toString().toStdString(), cv::Point2d(frameToDrawOn->cols - 370, frameToDrawOn->rows - 20), 5, 0.9, Scalar(255, 255, 255));
}

int LinesClass::countRulers()
{
    return _rulersList.count();
}
