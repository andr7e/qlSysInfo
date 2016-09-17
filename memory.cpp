#include <sys/sysinfo.h>
#include "systeminfo.h"
#include "utils.h"


bool SystemInfo::LoadMemoryInfo ()
{
    struct sysinfo sys_info;

    if (!sysinfo (&sys_info))
    {
        quint32 unit = sys_info.mem_unit;

        //qDebug() << Q_FUNC_INFO << unit; // 1 - x86_64, 4096 - i686

        totalMem_ = (quint32)(sys_info.totalram/1024*unit/1024);

        freeMem_ = (quint32)(sys_info.freeram/1024*unit/1024);

        //qDebug () << Q_FUNC_INFO << sys_info.freeram;

        totalSwap_ = (quint32)(sys_info.totalswap/1024*unit/1024);

        freeSwap_ = (quint32)(sys_info.freeswap/1024*unit/1024);

        return 1;
    }

    return 0;
}


/*
#define PROC_MEMINFO "/proc/meminfo"

#define KEY_MEM_TOTAL      "MemTotal"
#define KEY_MEM_FREE       "MemFree"
bool SystemInfo::LoadMemoryInfo ()
{
    QStringList keys;
    keys << KEY_MEM_TOTAL << KEY_MEM_FREE;


    QHash <QString, QString> info;
    if (Utils::ParseInfo (PROC_MEMINFO, info, keys))
    {
        QString totalMem = info[KEY_MEM_TOTAL];
        totalMem.remove (QRegExp("[^0-9]"));

        totalMem_ = totalMem.toInt()/1024;

        QString freeMem = info[KEY_MEM_FREE];

        freeMem.remove (QRegExp("[^0-9]"));

        freeMem_ = freeMem.toInt()/100;

        qDebug () << Q_FUNC_INFO << freeMem_;

        //freeMem_ = info [KEY_MEM_FREE].toInt();

        return 1;
    }
    return 0;
}
*/

quint32 SystemInfo::GetTotalMemory() const
{
    return totalMem_;
}

quint32 SystemInfo::GetFreeMemory() const
{
    return freeMem_;
}

quint32 SystemInfo::GetUsedMemory() const
{
    return totalMem_ - freeMem_;
}

quint32 SystemInfo:: GetTotalSwap() const
{
    return totalSwap_;
}

quint32 SystemInfo::GetFreeSwap() const
{
    return freeSwap_;
}

quint32 SystemInfo::GetUsedSwap() const
{
    return totalSwap_ - freeSwap_;
}


