#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
class SystemInfo;
}

class SystemInfo : public QMainWindow
{
    Q_OBJECT

private:
    Ui::SystemInfo *ui;

    //ReleaseInfo
    QString distroName_;
    QString releaseName_;


    //MemoryInfo
    quint32 totalMem_;
    quint32 freeMem_;
    quint32 totalSwap_;
    quint32 freeSwap_;

    //SysInfo
    QString hostname_;
    QString kernel_;
    QString kversion_;
    QString arch_;

    //Resolution
    quint32 screenW_;
    quint32 screenH_;

    //LspciInfo
    QHash <QString, QString> lspciInfo_;

    //CpuInfo
    QHash <QString, QString> cpuInfo_;

    //MotherboardInfo
    QHash <QString, QString> moboInfo_;

    QAction *refreshAction_;
    QAction *makeScreenshotAction_;

public:
    explicit SystemInfo(QWidget *parent = 0);
    ~SystemInfo();

    void createActions();

    //Release
    QString GetDistroName () const;
    QString GetReleaseName () const;

    //Memory
    quint32 GetTotalMemory() const;
    quint32 GetFreeMemory() const;
    quint32 GetUsedMemory() const;

    quint32 GetTotalSwap() const;
    quint32 GetFreeSwap() const;
    quint32 GetUsedSwap() const;

    //System
    QString GetHostname () const;
    QString GetKernel () const;
    QString GetKVersion () const;
    QString GetArch () const;

    //Lspci
    QString GetChipset () const;
    QString GetVideocard () const;
    QString GetAudiocard () const;
    QString GetEthernet () const;
    QString GetNetwork () const;

    //Cpu
    QString GetCpuVendor () const;
    QString GetCpuModelName () const;
    QString GetCpuCores () const;
    QString GetCpuCoreClock () const;
    QString GetCpuCacheSize () const;
    QString GetCpuBogomips () const;
    QString GetCpuFamily () const;
    QString GetCpuModel () const;
    QString GetCpuStepping () const;

    //Motherboard
    QString GetMotherboardManufacturer () const;
    QString GetMotherboardModel () const;

    QString GetBiosVendor () const;
    QString GetBiosVersion () const;
    QString GetBiosDate () const;

    //
    QString getDrivesInfo () const;

    //Loading
    bool LoadReleaseInfo ();
    bool LoadMotherboardInfo ();
    bool LoadMemoryInfo ();
    bool LoadSystemInfo ();
    bool LoadLspciInfo ();
    bool LoadCpuInfo ();

    void LoadAllInfo ();
    void copyDataToView ();

private slots:
    void refresh();
    void makeScreenshot();
};

#endif // SYSTEMINFO_H
