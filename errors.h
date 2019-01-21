#ifndef ERRORS_H
#define ERRORS_H

#include <QString>
#include <QDebug>

class Errors
{
public:
    void fatalError(QString errorMessage);
};

#endif // ERRORS_H
