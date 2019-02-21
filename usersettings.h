#ifndef USERSETTINGS_H
#define USERSETTINGS_H

// QtIncludes //
#include <QSettings>
#include <QVariant>
#include <QString>

// Local includes //
#include "errors.h"

struct Options
{
    unsigned char zoom;
    unsigned char focus;
    unsigned char contrast;
    unsigned char saturation;
    unsigned char brightness;
    bool autoFocus;
};

class UserSettings
{
public:
    static void saveSettings(const QString &key, const QVariant &value, const QString &group);
    static QVariant loadSettings(const QString &key, const QVariant &defaultValue, const QString &group);
};

#endif // USERSETTINGS_H
