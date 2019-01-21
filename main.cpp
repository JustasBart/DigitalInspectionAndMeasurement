#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    a.setApplicationName("DigitalInspectionAndMeasurement");
    a.setOrganizationName("B00086463");
    a.setOrganizationDomain("http://www.itb.ie");

    w.show();

    return a.exec(); 
}
