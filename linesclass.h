#ifndef LINESCLASS_H
#define LINESCLASS_H

// QtIncludes //
#include <QPoint>

// Generic includes //
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <vector>

using namespace std;

class LinesClass
{
public:
    LinesClass();


private:
    QPoint _point1;
    QPoint _point2;

    static double _PXtoMM;
    static vector <QPoint> rulerPoints;
};

#endif // LINESCLASS_H
