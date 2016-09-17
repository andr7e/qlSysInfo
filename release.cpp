#include <QFile>
#include "systeminfo.h"

#define ETC_RELEASE "/etc/lsb-release"

#define KEY_DISTR_ID       "DISTRIB_ID="
#define KEY_DISTR_RELEASE  "DISTRIB_RELEASE="
#define KEY_DISTR_CODENAME "DISTRIB_CODENAME="

bool SystemInfo::LoadReleaseInfo ()
{
    QStringList distrList;
    distrList << KEY_DISTR_ID << KEY_DISTR_RELEASE << KEY_DISTR_CODENAME;

    QFile fd (ETC_RELEASE);

    fd.open(QIODevice::ReadOnly);

    if (fd.isOpen())
    {
        while (!fd.atEnd())
        {
            int ind = 0;
            QString line = fd.readLine ();
            line.remove ("\n");

            //qDebug () << Q_FUNC_INFO << line;

            ind = line.indexOf (KEY_DISTR_ID);
            if (ind >= 0)
            {
                line.remove (KEY_DISTR_ID);
                distroName_ = line;
            }
            else
            {
                ind = line.indexOf (KEY_DISTR_RELEASE);
                if (ind >= 0)
                {
                    line.remove (KEY_DISTR_RELEASE);
                    releaseName_ = line;
                }
                else
                {
                    ind = line.indexOf (KEY_DISTR_CODENAME);
                    if (ind >= 0)
                    {
                        line.remove (KEY_DISTR_CODENAME);
                        releaseName_.append (" ");
                        releaseName_.append (line);
                    }
                }
            }
        }

        fd.close();

        return 1;
    }

    return 0;
}

QString SystemInfo::GetDistroName () const
{
    return distroName_;
}

QString SystemInfo::GetReleaseName () const
{
    return releaseName_;
}
