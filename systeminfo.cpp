#include "systeminfo.h"
#include "ui_systeminfo.h"

#include <QDesktopWidget>
#include <QFileDialog>

#define APP_ICON_STRING ":/images/iconsysinfo.png"

SystemInfo::SystemInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemInfo)
{
    ui->setupUi(this);

    LoadAllInfo ();

    createActions();

    copyDataToView ();

    setWindowIcon(QIcon(APP_ICON_STRING));
}

SystemInfo::~SystemInfo()
{
    delete ui;
}

void SystemInfo::createActions()
{
    refreshAction_ = new QAction(QIcon::fromTheme("view-refresh"), tr("Refresh"), this);
    refreshAction_->setShortcut(QKeySequence::Refresh);
    connect(refreshAction_, SIGNAL(triggered()), SLOT(refresh()));

    makeScreenshotAction_ = new QAction(QIcon::fromTheme("insert-image", QIcon(":/images/screenshot.png")), tr("Make Screenshot"), this);
    connect(makeScreenshotAction_, SIGNAL(triggered()), SLOT(makeScreenshot()));

    addAction(refreshAction_);

    ui->toolBar->addAction(refreshAction_);
    ui->toolBar->addAction(makeScreenshotAction_);
}

void SystemInfo::LoadAllInfo ()
{
    LoadReleaseInfo ();
    LoadMotherboardInfo ();
    LoadMemoryInfo ();
    LoadSystemInfo ();
    LoadLspciInfo ();
    LoadCpuInfo ();

    QDesktopWidget desktop;
    screenW_ = desktop.width();
    screenH_ = desktop.height();
}

void SystemInfo::copyDataToView ()
{
    QString tmp;

    ui->lineEdit_mb1->setText (GetMotherboardManufacturer());
    ui->lineEdit_mb2->setText (GetMotherboardModel());
    ui->lineEdit_mb3->setText (GetChipset());
    ui->lineEdit_mb4->setText (GetBiosVendor());
    ui->lineEdit_mb5->setText (GetBiosVersion());
    ui->lineEdit_mb6->setText (GetBiosDate());

    ui->lineEdit_cpu1->setText (GetCpuVendor());
    ui->lineEdit_cpu2->setText (GetCpuModelName());
    ui->lineEdit_cpu3->setText (GetCpuCores());
    ui->lineEdit_cpu4->setText (GetCpuCoreClock() + " MHz");
    ui->lineEdit_cpu5->setText (GetCpuCacheSize());
    ui->lineEdit_cpu6->setText (GetCpuBogomips());

    ui->lineEdit_sys1->setText (GetDistroName() + ' ' + GetReleaseName());
    ui->lineEdit_sys2->setText (GetHostname());
    ui->lineEdit_sys3->setText (GetArch());
    ui->lineEdit_sys4->setText (GetKernel());
    ui->lineEdit_sys5->setText (GetKVersion());

    tmp.sprintf ("%dx%d", screenW_, screenH_);
    ui->lineEdit_sys6->setText (tmp);

    ui->textEdit_dev1->setText (GetVideocard());

    ui->textEdit_dev2->setText (GetAudiocard());

    ui->textEdit_dev3->setText (GetEthernet() + '\n' + GetNetwork());

    //
    tmp.sprintf ("%d/%d Mb", GetUsedMemory(), GetTotalMemory());
    ui->lineEdit_mem1->setText (tmp);
    ui->progressBar_1->setRange (0, GetTotalMemory());
    ui->progressBar_1->setValue (GetUsedMemory());

    tmp.sprintf ("%d/%d Mb", GetUsedSwap(), GetTotalSwap());
    ui->lineEdit_mem2->setText (tmp);
    ui->progressBar_2->setRange (0, GetTotalSwap());
    ui->progressBar_2->setValue (GetUsedSwap());

    ui->label_com1->setText ("<html><head/><body><p><span style='font-size:14pt; font-weight:600;'>" + GetHostname () + "</span></p></body></html>");
    ui->label_com2->setText ("<html><head/><body><p><span style='font-size:14pt; font-weight:600;'>" + GetDistroName () + "</span></p></body></html>");
    ui->label_com3->setText ("Release " + GetReleaseName ());
    ui->label_com4->setText ("Kernel " + GetKernel () + " " + GetArch ());

    tmp.sprintf ("%0.1f GiB", GetTotalMemory ()/1024.);
    ui->label_com7->setText ("Memory: " +  tmp);
    ui->label_com6->setText ("CPU: " + GetCpuModelName() + " x " + GetCpuCores());

    QIcon icon (APP_ICON_STRING);
    ui->iconLabel->setPixmap(icon.pixmap(QSize (70,70)));
}

void SystemInfo::refresh()
{
    LoadAllInfo ();

    copyDataToView ();
}

void SystemInfo::makeScreenshot()
{
    QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(), pos().x(), pos().y(), size().width() + 5, size().height() + 30);

    QString format = "png";
    QString initialPath = QDir::currentPath() + tr("/screenshot.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(format.toUpper())
                               .arg(format));

    if (!fileName.isEmpty()) pixmap.save(fileName, format.toLatin1());
}
