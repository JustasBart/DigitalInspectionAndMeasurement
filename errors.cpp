#include "errors.h"

Q_NORETURN void Errors::fatalError(QString errorMessage)
{
    qDebug() << "CRICITAL ERROR: " + errorMessage;
    QApplication::closeAllWindows();
    exit(EXIT_FAILURE);
}

void Errors::cameraOpenErrorWindow()
{
    QMessageBox msgBox;

    msgBox.setText("The camera port refused to open...");
    msgBox.setInformativeText("Would you like to try opening a default port?\nThe default Port is 0.");

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
        case QMessageBox::Cancel:
            Errors::fatalError("The user cancelled opening the default camera port.");
        default:
            fatalError("Unexpected error occured in 'cameraOpenErrorWindow'");
    }
}

int Errors::cameraPositionUncalibrated()
{
    QMessageBox msgBox;

    msgBox.setText("The camera position is uncalibrated...");
    msgBox.setInformativeText("The measurements cannot be applied to an uncalibrated setup.\nWould you like to calibrate the camera positioning now?");

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);

    int ret = msgBox.exec();

    switch (ret)
    {
        case QMessageBox::Yes:
        {
            qDebug() << "User chose to calibrate the camera.";
            return 0;
        }
        case QMessageBox::Cancel:
        {
            qDebug() << "User canceled the measurements mode.";
            return 1;
        }
        default:
            fatalError("Unexpected error occured in 'cameraPositionUncalibrated'");
    }
}

int Errors::clearAllRulersErrorWindow()
{
    QMessageBox msgBox;

    msgBox.setText("Deleting all rulers...");
    msgBox.setInformativeText("Are you sure you want to delete all of the rulers currently placed?");

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    int ret = msgBox.exec();

    switch (ret)
    {
        case QMessageBox::Yes:
        {
            qDebug() << "User chose to delete the rulers.";
            return 0;
        }
        case QMessageBox::No:
        {
            qDebug() << "User canceled the deletion of all rulers.";
            return 1;
        }
        default:
            fatalError("Unexpected error occured in 'clearAllRulersErrorWindow'");
    }
}

void Errors::serialConnectionError()
{
    QMessageBox msgBox;

    msgBox.setText("Serial connection error...");
    msgBox.setInformativeText("Unable to locate the Arduino board!");
    msgBox.setStandardButtons(QMessageBox::Ok);

    msgBox.exec();

    return;
}

void Errors::serialNoEnumsFound()
{
    QMessageBox msgBox;

    msgBox.setText("Serial ports enumeration");
    msgBox.setInformativeText("No Serial Ports enumerations found.\nPlease ensure that the Arduino board USB cable is connected properly.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void Errors::serialIsAlreadyConnected()
{
    QMessageBox msgBox;

    msgBox.setText("Connection already established");
    msgBox.setInformativeText("The Serial connection with the board is already established.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}
