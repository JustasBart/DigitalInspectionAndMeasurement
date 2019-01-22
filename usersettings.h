#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include "options.h"
#include <QString>
#include <QVariant>
#include <QSettings>

#include "errors.h"

#define FILE_PATH "Options.txt"

class UserSettings
{
public:
    static void saveSettings(const QString &key, const QVariant &value, const QString &group);
    static QVariant loadSettings(const QString &key, const QVariant &defaultValue, const QString &group);
};

#endif // USERSETTINGS_H
