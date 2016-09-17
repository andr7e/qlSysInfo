#include <QApplication>

#include "systeminfo.h"

#define APP_NAME "qlSysInfo"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SystemInfo w;

    w.setWindowTitle(APP_NAME);

    w.show();
    
    return a.exec();
}
