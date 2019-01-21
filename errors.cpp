#include "errors.h"

void fatalError(QString errorMessage)
{
    qDebug() << "CRICITAL ERROR: " + errorMessage;
}
