#include "settingshandler.h"

Settings::Settings()
{
#ifdef DEBUG
    qDebug() << "Settings class running...";
#endif
}

void Settings::loadSettings()
{
#ifdef DEBUG
    qDebug() << "Loading program settings...\n";
#endif
    // QDir::setCurrent(QCoreApplication::applicationDirPath());

    settingsFileLocation = QCoreApplication::applicationDirPath() + "\ projectGUISettings.txt";

    settingsFile.fileName() = settingsFileLocation;

    if ( settingsFile.open(QIODevice::ReadWrite) )
    {
        readSettings();
    }
    else
    {
        qDebug() << "The settings file was not found!\nResulting to default settings...";
    }

    settingsFile.close();
}

void Settings::readSettings()
{
    settingsStream.setDevice( &settingsFile );

    while(!settingsStream.atEnd())
    {
        optionsLine = settingsStream.readLine();
        projectOptions += optionsLine;
    }
}

void Settings::saveSettings()
{
    qDebug() << "Saving program settings...\n";
}
