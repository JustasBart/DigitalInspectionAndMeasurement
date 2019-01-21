#include "usersettings.h"

void UserSettings::readSettings(Options &optionsBuffer)
{
    // Options options;
    QString buffer;

    if (readFromFile(FILE_PATH, buffer))
    {
        QStringList optionsList = buffer.split( "\n" );

        QString neededWord = optionsList.value( 0 );

        qDebug() << neededWord;
    }
    else
    {
        Errors::fatalError("Could not read the settings file!");
    }
}

void UserSettings::saveSettings(Options &optionsBuffer)
{

}

bool UserSettings::writeToFile(const QString &filePath, QString &buffer)
{
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream( &file );
        stream >> buffer;

        return true;
    }
    else
    {
        Errors::fatalError("The file: [" + filePath + "] can not be written to!");
    }

    return false;
}

bool UserSettings::readFromFile(const QString &filePath, QString &buffer)
{
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream( &file );
        stream << buffer << endl;

        return true;
    }
    else
    {
        Errors::fatalError("The file: [" + filePath + "] can not be read from!");
    }

    return false;
}
