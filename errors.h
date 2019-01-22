#ifndef ERRORS_H
#define ERRORS_H

#include <QString>
#include <QDebug>
#include <QMessageBox>

class Errors
{
public:
    static void fatalError(QString errorMessage);
    static void windowFatalError(QString errorMessage, QString infoText);
};

#endif // ERRORS_H
