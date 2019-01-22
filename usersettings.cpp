#include "usersettings.h"

#include <QString>

void UserSettings::saveSettings(const QString &key, const QVariant &value, const QString &group)
{
    QSettings settings("Soft", "Project");

    if (!settings.isWritable())
    {
        Errors::fatalError("The settings cannot be saved.");
    }

    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.endGroup();
}

QVariant UserSettings::loadSettings(const QString &key, const QVariant &defaultValue, const QString &group)
{
    QSettings settings("Soft", "Project");

    settings.beginGroup(group);
    QVariant value = settings.value(key, defaultValue);
    settings.endGroup();

    return value;
}
