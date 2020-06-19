#include "lockfilereader.h"
#include <QFile>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QDebug>
#include <QFileInfo>

bool isFileExist(QString filePath)
{
    QFileInfo fileInfo(filePath);
    if (fileInfo.isFile()) {
        return true;
    }
    return false;
}

LockFileReader::LockFileReader(QObject *parent) : QObject(parent)
{
    //setGamePath("D:\\Software\\Relax\\LOL\\英雄联盟\\LeagueClient");
}

bool LockFileReader::setGamePath(const QString &path)
{
    m_lockFileInfo.name = QString("unknow");
    m_lockFileInfo.uid = QString("unknow");
    m_lockFileInfo.port = QString("unknow");
    m_lockFileInfo.token = QString("unknow");
    m_lockFileInfo.protocol = QString("unknow");

    // 加载文件
    QString filePath = path + "/lockfile";
    qDebug() << filePath;
    if (!isFileExist(filePath)) {
        QMessageBox::warning(nullptr, "错误!", "请检查游戏是否正在运行并重试.\n"
                                             "如游戏已启动依旧无法获取请重启软件或大厅客户端!");
        return false;
    }
    QFile loadFile(filePath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "错误!", "文件打开失败!请检查路径并重试!");
        return false;
    }

    // 读取文件内容并关闭句柄
    QString allData = loadFile.readAll();
    loadFile.close();

    // 正则表达式取内容
    QString pattern("(.*):(.*):(.*):(.*):(.*)");
    QRegExp rx(pattern);
    if (rx.exactMatch(allData)) {
        m_lockFileInfo.name = rx.cap(1);
        m_lockFileInfo.uid = rx.cap(2);
        m_lockFileInfo.port = rx.cap(3);
        m_lockFileInfo.token = rx.cap(4);
        m_lockFileInfo.protocol = rx.cap(5);

        qDebug() << m_lockFileInfo.name << "\n"
                 << m_lockFileInfo.uid << "\n"
                 << m_lockFileInfo.port << "\n"
                 << m_lockFileInfo.token << "\n"
                 << m_lockFileInfo.protocol << "\n";
    } else {
        QMessageBox::warning(nullptr, "错误!", "获取失败，请检查游戏是否正在运行！");
        return false;
    }
    return true;
}

QString LockFileReader::getPort()
{
    return m_lockFileInfo.port;
}

QString LockFileReader::getToken()
{
    return m_lockFileInfo.token;
}

LockFileInfo LockFileReader::getInfo()
{
    return m_lockFileInfo;
}
