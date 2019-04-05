#ifndef SERIALCOMMS_H
#define SERIALCOMMS_H

// QtIncludes //
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QtDebug>
#include <QObject>
#include <QString>

// Local includes //
#include "errors.h"

class SerialComms
{
public:
    SerialComms(QString portNumber);
    ~SerialComms();
    static QString getUSBEnumerations();
    int sendData();
    int receiveData();

private:
    QSerialPort *_serial;
    QString _serialPortString;
};

#endif // SERIALCOMMS_H
