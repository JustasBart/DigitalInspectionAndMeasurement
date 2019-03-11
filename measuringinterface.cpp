#include "measuringinterface.h"
#include "ui_measuringinterface.h"

using namespace cv;

MeasuringInterface::MeasuringInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasuringInterface),
    _lClassObj(new LinesClass()),
    _rulerDrawingStatus(false),
    _scaleDrawingStatus(false),
    _screenWidth(0),
    _screenHeight(0),
    _mappedPoint1(0, 0),
    _mappedPoint2(0, 0)
{
    ui->setupUi(this);

    connect(ui->frameLabel, SIGNAL(sendMousePosition(QPoint&)), this, SLOT(labelMousePos(QPoint&)));
    connect(ui->frameLabel, SIGNAL(sendMousePoint(QPoint&)), this, SLOT(labelMouseClickedPos(QPoint&)));
    connect(MeasuringInterface::window(), SIGNAL(sendTableObject(QTableView&)), _lClassObj, SLOT(receiveTableObject(QTableView&)));
    connect(MeasuringInterface::window(), SIGNAL(removeRulerAtIndex(int)), _lClassObj, SLOT(removeRuler(int)));
    connect(MeasuringInterface::window(), SIGNAL(removeAllRulers()), _lClassObj, SLOT(removeRulers()));
}
MeasuringInterface::~MeasuringInterface()
{
    delete ui;
}
