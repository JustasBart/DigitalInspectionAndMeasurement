#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // a.setApplicationName("DigitalInspectionAndMeasurement");
    // a.setOrganizationName("B00086463");

    w.show();

    return a.exec(); 
}
