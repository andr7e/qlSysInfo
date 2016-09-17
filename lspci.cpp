#include <stdio.h>
#include "systeminfo.h"

#define KEY_HOST "Host"
#define KEY_VGA "VGA"
#define KEY_AUDIO "Audio"
#define KEY_ETHERNET "Ethernet"
#define KEY_NETWORK "Network"

//type - line count, host bridge one, other can be 2
QString makeCorrectingLspci (const char *buf, int type)
{
    QString res;

    if (buf)
    {
        QString bufStr (buf);
        QStringList strList = bufStr.split('\n');

        for (int i=0; i < qMin<int>(strList.size ()-1, type); i++)
        {
            int ind = strList[i].indexOf (" ");
            strList[i].remove(0, ind);

            ind = strList[i].indexOf (":");
            strList[i].remove(0, ind+2);

            if (i != 0) res +='\n';
            res += strList[i];
        }
    }

    return res;
}

#define BUF_MAX_SIZE 1024
#define LSPCI "lspci"

bool SystemInfo::LoadLspciInfo ()
{
    char buf[BUF_MAX_SIZE];
    char path[256];

    QStringList lspciList;

    lspciList << KEY_HOST << KEY_VGA << KEY_AUDIO << KEY_ETHERNET << KEY_NETWORK;

    for (int i=0; i < lspciList.size(); i++)
    {
        QString key = lspciList[i];

        sprintf (path, "%s | grep %s", LSPCI, key.toStdString().c_str());

        FILE *fd = popen (path, "r");

        if (fd)
        {
            memset (buf, 0, sizeof(buf));

            fread (buf, BUF_MAX_SIZE-1, 1, fd);

            lspciInfo_[key] = makeCorrectingLspci (buf, i==0? 1 : 2);

            fclose (fd);
        }
    }

    return 1;
}

QString SystemInfo::GetChipset () const
{
    return lspciInfo_[KEY_HOST];
}

QString SystemInfo::GetVideocard () const
{
    return lspciInfo_[KEY_VGA];
}

QString SystemInfo::GetAudiocard () const
{
    return lspciInfo_[KEY_AUDIO];
}

QString SystemInfo::GetEthernet () const
{
    return lspciInfo_[KEY_ETHERNET];
}

QString SystemInfo::GetNetwork () const
{
    return lspciInfo_[KEY_NETWORK];
}
