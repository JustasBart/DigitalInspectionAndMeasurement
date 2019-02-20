#ifndef ERRORS_H
#define ERRORS_H

#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

class Errors
{
public:
    static void fatalError(QString errorMessage);
    static void cameraOpenErrorWindow();
    static int cameraPositionUncalibrated();
};

#endif // ERRORS_H
