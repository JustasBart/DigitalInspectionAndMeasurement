#ifndef ERRORS_H
#define ERRORS_H

#include <QString>
#include <QDebug>
#include <QMessageBox>

class Errors
{
public:
    static void fatalError(QString errorMessage);
    static void cameraOpenErrorWindow();
};

#endif // ERRORS_H
