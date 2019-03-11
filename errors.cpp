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

void Errors::clearAllRulersErrorWindow()
{

}
