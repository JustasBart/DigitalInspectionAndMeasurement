#include "errors.h"

void Errors::fatalError(QString errorMessage)
{
    qDebug() << "CRICITAL ERROR: " + errorMessage;
    exit(EXIT_FAILURE);
}
