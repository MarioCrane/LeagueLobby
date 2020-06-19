#include "lobbymanager.h"

const QString SummonerUrl = "/lol-summoner/v1/current-summoner";

LobbyManager::LobbyManager()
{
    m_url = "";
}

void LobbyManager::setLoginKey(const QString &port, const QString &token)
{
    m_port = port;
    m_token = token;
    m_url = QString("https://riot:%1@127.0.0.1:%2/lol-lobby/v2/lobby").arg(token).arg(port);
}

void LobbyManager::getSummonerInfo()
{
    getRequest(QString("https://riot:%1@127.0.0.1:%2%3").arg(m_token).arg(m_port).arg(SummonerUrl));
}

void LobbyManager::createLobbyFromJson(const QString &json)
{
    postRequest(m_url, json);
}

/* http://static.developer.riotgames.com/docs/lol/queues.json */
void LobbyManager::createLobbyFromQueueId(const quint16 &id)
{
    postRequest(m_url, QString("{\"queueId\":%1}").arg(id));
}

void LobbyManager::create5V5Tutorial(const QString &lobbyName, const quint8 &teamSize)
{
    /***********************************
     * {
     *     "customGameLobby": {
     *         "configuration": {
     *             "gameMode": "PRACTICETOOL",
     *             "gameMutator": "",
     *             "gameServerRegion": "",
     *             "mapId": 11,
     *             "mutators": {
     *                 "id": 1
     *             },
     *             "spectatorPolicy": "AllAllowed",
     *             "teamSize": 5
     *         },
     *         "lobbyName": "MyLobby",
     *         "lobbyPassword": null
     *     },
     *	   "isCustom": true
     * }
     ***********************************/

    // Create JSON

    QJsonObject mutators;
    mutators.insert("id", 1);

    QJsonObject config;
    config.insert("gameMode", "PRACTICETOOL");
    config.insert("gameMutator", "");
    config.insert("gameServerRegion", "");
    config.insert("mapId", 11);
    config.insert("mutators", QJsonValue(mutators));
    config.insert("spectatorPolicy", "AllAllowed");
    config.insert("teamSize", teamSize);

    QJsonObject custom;
    custom.insert("configuration", QJsonValue(config));
    custom.insert("lobbyName", lobbyName);
    custom.insert("lobbyPassword", QJsonValue::Null);

    QJsonObject main;
    main.insert("customGameLobby", QJsonValue(custom));
    main.insert("isCustom", true);

    QJsonDocument document;
    document.setObject(main);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    createLobbyFromJson(strJson);
}

void LobbyManager::onReplyFinished(QNetworkReply *reply)
{
    // Get reply string then abort it.
    QByteArray bytes = reply->readAll();

    if (reply->url().toString().right(SummonerUrl.length()) == SummonerUrl) {
        // Get Summoner informations
        SummonerInfo info;
        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
        if (jsonError.error == QJsonParseError::NoError) {
            if (doucment.isObject()) {
                QJsonObject object = doucment.object();
                // Name
                if (object.contains("displayName")) {
                    QJsonValue name = object.take("displayName");
                    if (name.isString()) {
                        info.name = name.toString();
                    }
                }
                // Id
                if (object.contains("summonerId")) {
                    QJsonValue id = object.take("summonerId");
                    if (id.isDouble()) {
                        info.id = id.toVariant().toInt();
                    }
                }
                // Level
                if (object.contains("summonerLevel")) {
                    QJsonValue level = object.take("summonerLevel");
                    if (level.isDouble()) {
                        info.level = level.toVariant().toInt();
                    }
                }
                // XP
                if (object.contains("xpSinceLastLevel")) {
                    QJsonValue xp = object.take("xpSinceLastLevel");
                    if (xp.isDouble()) {
                        info.xp = xp.toVariant().toInt();
                    }
                }
                // Next XP
                if (object.contains("xpUntilNextLevel")) {
                    QJsonValue nextXp = object.take("xpUntilNextLevel");
                    if (nextXp.isDouble()) {
                        info.nextXp = nextXp.toVariant().toInt();
                    }
                }
            }
        }
        emit summonerInfo(info);
    }

    // Clean
    reply->abort();
    reply->close();
    reply->deleteLater();
    reply = NULL;

    QString resultStr = bytes;
    qDebug() << resultStr;
    emit result(resultStr);
}
