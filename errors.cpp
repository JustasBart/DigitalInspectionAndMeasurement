#include "errors.h"

void Errors::fatalError(QString errorMessage)
{
    qDebug() << "CRICITAL ERROR: " + errorMessage;
    exit(EXIT_FAILURE);
}

void Errors::windowFatalError(QString errorMessage, QString infoText)
{
    QMessageBox msgBox;

    msgBox.setText(errorMessage);
    msgBox.setInformativeText(infoText);

    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Ok);

    int ret = msgBox.exec();

    switch (ret)
    {
        case QMessageBox::Ok:
            qDebug() << "Trying to re-open the camera on the default port.";
            break;
        case QMessageBox::Close:
            Errors::fatalError("The user closed the application.");
            break;
        case QMessageBox::Cancel:
            Errors::fatalError("The user cancelled opening the default camera port.");
            break;
        default:
            fatalError("Unexpected error occured in 'windowFatalError'");
            break;
    }
}
