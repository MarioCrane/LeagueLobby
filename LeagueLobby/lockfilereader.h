#ifndef LOCKFILEREADER_H
#define LOCKFILEREADER_H

/**
* @projectName   LeagueLobby
* @brief         lockfile相关操作
* @author        Mario
* @date          2020-06-19
*/

#include <QObject>

/**
 * @brief Lock文件相关信息
 */
struct LockFileInfo {
    QString name;
    QString uid;
    QString port;
    QString token;
    QString protocol;
};

class LockFileReader : public QObject
{
    Q_OBJECT
public:
    explicit LockFileReader(QObject *parent = nullptr);

    /**
     * @brief 设置游戏路径并读取lockfile
     * @param path 游戏路径，需是LeagueClient目录下
     * @return 返回lockfile的读取状态，True为成功、False为失败
     */
    bool setGamePath(const QString &path);

    /**
     * @brief 获取lockfile内存放的端口号，也就是HTTP服务器开放的端口号
     * @return 返回字符串格式的端口号文本
     */
    QString getPort();

    /**
     * @brief 获取lockfile内存放的令牌，登录HTTP服务器时需要
     * @return 返回字符串格式的令牌文本
     */
    QString getToken();

    /**
     * @brief 获取lockfile文件中存放的所有信息
     * @return 返回结构体
     */
    LockFileInfo getInfo();

signals:

private:
    LockFileInfo m_lockFileInfo;
};

#endif // LOCKFILEREADER_H
