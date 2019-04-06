#ifndef SERIALCOMMS_H
#define SERIALCOMMS_H

// QtIncludes //
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QtDebug>
#include <QObject>
#include <QString>
#include <QList>

// Local includes //
#include "errors.h"

class PortsClass
{
public:
    void setPort(QString newPort);
    void setLocation(QString newLocation);
    void setDescription(QString newDescription);
    void setManufacturer(QString newManufacturer);
    void setSerialNumber(QString newSerialNumber);
    void setVendorID(QString newVendorID);
    void setProductID(QString newProductID);
    void setBusyState(QString newBusyState);

    QString getPort();
    QString getLocation();
    QString getDescription();
    QString getManufacturer();
    QString getSerialNumber();
    QString getVendorID();
    QString getProductID();
    QString getBusyState();

private:
    QString _port;
    QString _location;
    QString _description;
    QString _manufacturer;
    QString _serialNumber;
    QString _vendorID;
    QString _productID;
    QString _busyState;
};

class SerialComms
{
public:
    SerialComms();
    ~SerialComms();
    void connectToSerial(QString vendorID, QString productID);

    QList<QString> getSerialEnumerations();
    int serialIsConnected(QString vendorID, QString productID);
    QByteArray receiveData();
    int sendData(QString data);

private:
    int initSerialComms(QString portNumber);
    void getComPortsEnums();

    QSerialPort *_serial;
    QList<PortsClass> _availablePorts;
};

#endif // SERIALCOMMS_H
