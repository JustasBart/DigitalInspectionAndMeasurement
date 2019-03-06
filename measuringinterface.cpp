#include "measuringinterface.h"
#include "ui_measuringinterface.h"

using namespace cv;

MeasuringInterface::MeasuringInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasuringInterface),
    _lClassObj(new LinesClass()),
    _rulerDrawingStatus(false),
    _screenWidth(0),
    _screenHeight(0),
    _scaleLinePoints(),
    _scaleDrawingIndex(0),
    _mappedPoint1(0),
    _mappedPoint2(0)
{
    ui->setupUi(this);

    connect(ui->frameLabel, SIGNAL(sendMousePosition(QPoint&)), this, SLOT(labelMousePos(QPoint&)));
    connect(ui->frameLabel, SIGNAL(sendMousePoint(QPoint&)), this, SLOT(labelMouseClickedPos(QPoint&)));
    connect(MeasuringInterface::window(), SIGNAL(sendTableObject(QTableView&)), _lClassObj, SLOT(receiveTableObject(QTableView&)));
}
MeasuringInterface::~MeasuringInterface()
{
    delete ui;
}


void MeasuringInterface::on_rulersTable_doubleClicked(const QModelIndex &index)
{
    qDebug() << index.column();
}
