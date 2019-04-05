#ifndef ERRORS_H
#define ERRORS_H

// QtIncludes //

#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QDebug>

class Errors
{
public:
    static void fatalError(QString errorMessage);
    static void cameraOpenErrorWindow();
    static int clearAllRulersErrorWindow();
    static int cameraPositionUncalibrated();
    static void serialConnectionError(QString port);
};

#endif // ERRORS_H
