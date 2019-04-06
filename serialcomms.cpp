#include "serialcomms.h"

SerialComms::SerialComms()
{
    _serial = new QSerialPort;
}
SerialComms::~SerialComms()
{
    _serial->close();
}

void SerialComms::getComPortsEnums()
{
    _availablePorts.clear();
    PortsClass tempObj;

    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : infos)
    {
        tempObj.setPort( info.portName() );
        tempObj.setLocation( info.systemLocation() );
        tempObj.setDescription( info.description() );
        tempObj.setManufacturer( info.manufacturer() );
        tempObj.setSerialNumber( info.serialNumber() );
        tempObj.setVendorID( info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : "-1" );
        tempObj.setProductID( info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : "-1" );
        tempObj.setBusyState( info.isBusy() ? "Yes" : "No" );

        _availablePorts.push_back(tempObj);
    }
}

int SerialComms::initSerialComms(QString portNumber)
{
    int status = -1;

    _serial->setPortName(portNumber);
    _serial->setBaudRate(QSerialPort::Baud9600);
    _serial->setDataBits(QSerialPort::Data8);
    _serial->setParity(QSerialPort::NoParity);
    _serial->setStopBits(QSerialPort::OneStop);
    _serial->setFlowControl(QSerialPort::NoFlowControl);

    if (_serial->open(QIODevice::ReadWrite))
    {
        status = 0;

        qDebug() << "Port is now ready (Connected).";
    }
    else
    {
        qDebug() << "The Communications port " + portNumber + " could not be opened.";
    }

    return status;
}

void SerialComms::connectToSerial(QString vendorID, QString productID)
{
    qDebug() << "Enumerating the Serial ports...";
    getComPortsEnums();

    if (_availablePorts.count() > 0)
    {
        qDebug() << "Found at least one possible Serial port!";

        for (int i = 0; i < _availablePorts.count(); i++)
        {
            qDebug() << "Trying to match the Serial board with the ID's...";
            qDebug() << "Comparing:" << vendorID << "with:" << _availablePorts[i].getVendorID() << "- " "Comparing:" << productID << "with:" << _availablePorts[i].getProductID();

            if (_availablePorts[i].getVendorID() == vendorID && _availablePorts[i].getProductID() == productID)
            {
                qDebug() << "Located the Arduino board Serial Port!";

                if (_availablePorts[i].getBusyState() == "No")
                {
                    qDebug() << "Attemped to connect to the board...";
                    initSerialComms(_availablePorts[i].getPort());
                }
                else
                {
                    qDebug() << "Found the Arduino board, but the board is busy! Cannot connect!!!";
                }

                if (_serial->isOpen())
                    qDebug() << "Successfully connected to the Arduino board!";
                else
                {
                    qDebug() << "Could not connect to the board...";
                    Errors::serialConnectionError();
                }

                break;
            }
        }
    }
    else
    {
        Errors::serialConnectionError();
    }
}

bool SerialComms::serialIsConnected()
{
    if (_serial != nullptr)
    {
        if (_serial->isOpen())
            return true;
    }
    return false;
}

// Port Class
// **-----------------------------------** //

void PortsClass::setPort(QString newPort)
{
    _port = newPort;
}
void PortsClass::setLocation(QString newLocation)
{
    _location = newLocation;
}
void PortsClass::setDescription(QString newDescription)
{
    _description = newDescription;
}
void PortsClass::setManufacturer(QString newManufacturer)
{
    _manufacturer = newManufacturer;
}
void PortsClass::setSerialNumber(QString newSerialNumber)
{
    _serialNumber = newSerialNumber;
}
void PortsClass::setVendorID(QString newVendorID)
{
    _vendorID = newVendorID;
}
void PortsClass::setProductID(QString newProductID)
{
    _productID = newProductID;
}
void PortsClass::setBusyState(QString newBusyState)
{
    _busyState = newBusyState;
}

QString PortsClass::getPort()
{
    return _port;
}
QString PortsClass::getLocation()
{
    return _location;
}
QString PortsClass::getDescription()
{
    return _description;
}
QString PortsClass::getManufacturer()
{
    return _manufacturer;
}
QString PortsClass::getSerialNumber()
{
    return _serialNumber;
}
QString PortsClass::getVendorID()
{
    return _vendorID;
}
QString PortsClass::getProductID()
{
    return _productID;
}
QString PortsClass::getBusyState()
{
    return _busyState;
}
