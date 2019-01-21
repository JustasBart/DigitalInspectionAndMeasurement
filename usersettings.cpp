#include "usersettings.h"

void UserSettings::saveSettings(const QString &key, const QVariant &value, const QString &group)
{
    QSettings settings;

    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.endGroup();
}

QVariant UserSettings::loadSettings(const QString &key, const QVariant &defaultValue, const QString &group)
{
    QSettings settings;

    settings.beginGroup(group);
    QVariant value = settings.value(key, defaultValue);
    settings.endGroup();
    return value;
}
