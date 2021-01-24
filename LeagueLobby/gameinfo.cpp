#include "gameinfo.h"

#include <QProcess>
#include <QFile>
#include <QFileInfo>

const QString ExecutablePath = "ExecutablePath";

static bool isFileExist(QString filePath)
{
    return QFileInfo(filePath).isFile();
}

GameInfo::GameInfo()
{

}

QString GameInfo::getGamePath()
{
    QStringList pathList;
    QProcess process;
    process.start("wmic process where name='LeagueClient.exe' GET ExecutablePath");
    process.waitForFinished(-1);
    QString result = QString::fromLocal8Bit(process.readAllStandardOutput());
    if (result.left(ExecutablePath.length()) == ExecutablePath) {
        pathList = result.split("\n");
        pathList.removeFirst();
        pathList.removeLast();
        pathList.removeLast();

        QString path = pathList.first();
        path = path.trimmed();
        path = path.simplified();
        path.remove("LeagueClient.exe");
        return path;
    }
    return "";
}

GameInfo::LockFile GameInfo::getLockFile(const QString &gamePath)
{
    LockFile lockFile = { "", "" };
    QString filePath = gamePath + "/lockfile";
    if (!isFileExist(filePath))
        return lockFile;

    QFile loadFile(filePath);
    if (!loadFile.open(QIODevice::ReadOnly))
        return lockFile;
    QString allData = loadFile.readAll();
    loadFile.close();

    QString pattern("(.*):(.*):(.*):(.*):(.*)");
    QRegExp rx(pattern);
    if (rx.exactMatch(allData)) {
        //name = rx.cap(1);
        //uid = rx.cap(2);
        lockFile.port = rx.cap(3);
        lockFile.token = rx.cap(4);
        //protocol = rx.cap(5);
        return lockFile;
    }
    return lockFile;
}

