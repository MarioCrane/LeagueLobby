#ifndef LOBBYMANAGER_H
#define LOBBYMANAGER_H

/**
* @projectName   LeagueLobby
* @brief         自定义房间管理
* @author        Mario
* @date          2020-06-19
*/

#include <QObject>
#include "httpmanager.h"

/**
 * @brief 召唤师信息
 */
struct SummonerInfo
{
    QString name;
    int id = 0;
    int level = 0;
    int xp = 0;
    int nextXp = 0;
};

class LobbyManager : public HttpManager
{
    Q_OBJECT
public:
    LobbyManager();

    /**
     * @brief 设置登录所需的端口和令牌
     * @param port 端口
     * @param token 令牌
     */
    void setLoginKey(const QString &port, const QString &token);

    /**
     * @brief 获取召唤师信息，会通过HTTP先服务器发送请求
     *        结果通过summonerInfo信号传回
     */
    void getSummonerInfo();

    /**
     * @brief 根据Json创建房间
     * @param json
     */
    void createLobbyFromJson(const QString &json);

    /**
     * @brief 根据QueueId创建房间
     * @param id 相关的ID在 http://static.developer.riotgames.com/docs/lol/queues.json
     */
    void createLobbyFromQueueId(const quint16 &id);

    /**
     * @brief 创建5V5训练营
     * @param lobbyName 房间名
     * @param teamSize 团队内人数，默认为5
     */
    void create5V5Practice(const QString &lobbyName, const quint8 &teamSize = 5);

public slots:
    void onReplyFinished(QNetworkReply *reply) override;

signals:
    /**
     * @brief 召唤师信息信号，配合getSummonerInfo使用
     * @param info
     */
    void summonerInfo(const SummonerInfo &info);

private:
    QString m_url;
    QString m_port;
    QString m_token;
};

#endif // LOBBYMANAGER_H
