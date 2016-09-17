#include <fstream>
#include "systeminfo.h"

#define KEY_BOARD_VENDOR "board_vendor"
#define KEY_BOARD_NAME "board_name"
#define KEY_BIOS_VENDOR "bios_vendor"
#define KEY_BIOS_VER "bios_version"
#define KEY_BIOS_DATE "bios_date"

#define MOBO_BASE "/sys/devices/virtual/dmi/id/"

bool GetLineFromFile (const char *fname, char *line)
{
    std::ifstream in (fname);

    if (in)
    {
        in.getline (line, 255, '\n');
        in.close();
        return 1;
    }

    return 0;
}

bool GetMoboInfo (const char *key, char *value)
{
    char path[256];
    sprintf (path, "%s%s", MOBO_BASE, key);

    return GetLineFromFile (path, value);
}

bool SystemInfo::LoadMotherboardInfo ()
{
    QStringList moboList;
    moboList << KEY_BOARD_VENDOR << KEY_BOARD_NAME << KEY_BIOS_VENDOR << KEY_BIOS_VER << KEY_BIOS_DATE;

    char tmp[256];

    for (int i=0; i < moboList.size(); i++)
    {
        QString key = moboList[i];

        GetMoboInfo (key.toStdString().c_str(), tmp);

        moboInfo_[key] = (tmp);
    }

    return 1;
}

QString SystemInfo::GetMotherboardManufacturer () const
{
    return moboInfo_[KEY_BOARD_VENDOR];
}

QString SystemInfo::GetMotherboardModel () const
{
    return moboInfo_[KEY_BOARD_NAME];
}

QString SystemInfo::GetBiosVendor () const
{
    return moboInfo_[KEY_BIOS_VENDOR];
}

QString SystemInfo::GetBiosVersion () const
{
    return moboInfo_[KEY_BIOS_VER];
}

QString SystemInfo::GetBiosDate () const
{
    return moboInfo_[KEY_BIOS_DATE];
}




