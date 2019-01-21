#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include "options.h"
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include "errors.h"

#define FILE_PATH "Options.txt"

class UserSettings
{
public:
    static void readSettings(Options &optionsBuffer);
    static void saveSettings(Options &optionsBuffer);

private:
    static bool writeToFile(const QString &filePath, QString &buffer);
    static bool readFromFile(const QString &filePath, QString &buffer);
};

#endif // USERSETTINGS_H
