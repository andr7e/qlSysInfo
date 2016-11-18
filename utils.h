#ifndef UTILS_H
#define UTILS_H

#include <QStringList>
#include <QHash>

class Utils
{
public:
    Utils();

    static bool ParseInfo (const QString &fname, QHash <QString, QString> &map, const QStringList &keys);

    static QString readFile (const QString &fname);
};

#endif // UTILS_H
