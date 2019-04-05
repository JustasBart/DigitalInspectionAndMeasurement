#include "serialcomms.h"

SerialComms::SerialComms(QString portNumber)
{
    _serial = new QSerialPort();
    _serialPortString = portNumber;
    _serial->setPortName(_serialPortString);
    _serial->setBaudRate(QSerialPort::Baud9600);
    _serial->setDataBits(QSerialPort::Data8);
    _serial->setParity(QSerialPort::NoParity);
    _serial->setStopBits(QSerialPort::OneStop);
    _serial->setFlowControl(QSerialPort::NoFlowControl);

    if (_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Port is now ready (Connected).";


    }
    else
    {
        qDebug() << "The Communications port " + portNumber + " could not be opened.";
        Errors::serialConnectionError(_serialPortString);
    }
}

SerialComms::~SerialComms()
{
    _serial->close();
}

QString SerialComms::getUSBEnumerations()
{
    const auto infos = QSerialPortInfo::availablePorts();
    QString s;

    for (const QSerialPortInfo &info : infos)
    {
        s = QObject::tr("Port: ") + info.portName() + "\n"
        + QObject::tr("Location: ") + info.systemLocation() + "\n"
        + QObject::tr("Description: ") + info.description() + "\n"
        + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
        + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
        + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
        + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
        + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";
    }

    return s;
}
