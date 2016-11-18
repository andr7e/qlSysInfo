#include <QFile>

#include "utils.h"

Utils::Utils()
{
}

bool Utils::ParseInfo (const QString &fname, QHash <QString, QString> &map, const QStringList &keys)
{
    QFile fd(fname);

    fd.open (QIODevice::ReadOnly);

    if (fd.isOpen())
    {
        QString string = fd.readAll();
        fd.close ();

        QStringList lineList = string.split("\n");

        foreach (QString line, lineList)
        {
            foreach (QString key, keys)
            {
                int ind = line.indexOf(key);

                if (ind >= 0)
                {
                    line.remove (key);

                    ind = line.indexOf(":");
                    if (ind >= 0) line.remove (0, ind + 1);

                    map[key] = line.simplified();

                    break;
                }
            }
        }

        return 1;
    }

    return 0;
}

QString Utils::readFile (const QString &fname)
{
    QFile fd(fname);

    fd.open (QIODevice::ReadOnly);

    if (fd.isOpen())
    {
        QString str = fd.readAll();
        fd.close ();

        return str;
    }

    return QString();
}
