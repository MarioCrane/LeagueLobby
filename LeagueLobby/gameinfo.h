#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QString>

class GameInfo
{
public:
    GameInfo();

    struct LockFile
    {
        QString port;
        QString token;
    };

    static QString getGamePath();
    static LockFile getLockFile(const QString &gamePath);
};

#endif // GAMEINFO_H
