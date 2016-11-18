#include <QFile>

#include "systeminfo.h"
#include "utils.h"

#define PROC_CPUINFO "/proc/cpuinfo"
//#define PROC_MEMINFO "/proc/meminfo"

#define KEY_CPU_VENDOR      "vendor_id"
#define KEY_CPU_MODEL_NAME  "model name"
#define KEY_CPU_CORES       "cpu cores"
#define KEY_CPU_FREQ        "cpu MHz"
#define KEY_CPU_CACHE       "cache size"
#define KEY_CPU_BOGOMIPS    "bogomips"
#define KEY_CPU_FAMILY      "family"
#define KEY_CPU_MODEL       "model"
#define KEY_CPU_STEPPING    "stepping"

bool SystemInfo::LoadCpuInfo ()
{
    QStringList cpuKeys;

    cpuKeys << KEY_CPU_VENDOR
            << KEY_CPU_MODEL_NAME
            << KEY_CPU_CORES
            << KEY_CPU_FREQ
            << KEY_CPU_CACHE
            << KEY_CPU_BOGOMIPS
            << KEY_CPU_FAMILY
            << KEY_CPU_MODEL
            << KEY_CPU_STEPPING;

    return Utils::ParseInfo (PROC_CPUINFO, cpuInfo_, cpuKeys);
}

QString SystemInfo::GetCpuVendor () const
{
    return cpuInfo_[KEY_CPU_VENDOR];
}

QString SystemInfo::GetCpuModelName () const
{
    return cpuInfo_[KEY_CPU_MODEL_NAME];
}

QString SystemInfo::GetCpuCores () const
{
    return cpuInfo_[KEY_CPU_CORES];
}

QString SystemInfo::GetCpuCoreClock () const
{
    return cpuInfo_[KEY_CPU_FREQ];
}

QString SystemInfo::GetCpuCacheSize () const
{
    return cpuInfo_[KEY_CPU_CACHE];
}

QString SystemInfo::GetCpuBogomips () const
{
    return cpuInfo_[KEY_CPU_BOGOMIPS];
}

QString SystemInfo::GetCpuFamily () const
{
    return cpuInfo_[KEY_CPU_FAMILY];
}

QString SystemInfo::GetCpuModel () const
{
    return cpuInfo_[KEY_CPU_MODEL];
}

QString SystemInfo::GetCpuStepping () const
{
    return cpuInfo_[KEY_CPU_STEPPING];
}
