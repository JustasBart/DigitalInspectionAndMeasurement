#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>
#include <QStringList>

// Uncomment for Debug messages to appear \\
#define DEBUG

class Settings
{
public:
    Settings();
    void loadSettings();
    void saveSettings();
    void readSettings();

private:
    QTextStream settingsStream;
    QString settingsFileLocation;
    QFile settingsFile;

    QString optionsLine;
    QStringList projectOptions;
};

#endif // SETTINGSHANDLER_H
