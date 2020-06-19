#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

/**
* @projectName   LeagueLobby
* @brief         HTTP相关操作
* @author        Mario
* @date          2020-06-19
*/

#include <QObject>
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QNetworkReply>
#include <QJsonParseError>
#include <QJsonObject>

class HttpManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    HttpManager();
    ~HttpManager();

    QNetworkReply *postRequest(const QString &url, const QString &request);
    QNetworkReply *getRequest(const QString &url);

signals:
    void result(const QString&);

private slots:
    virtual void onReplyFinished(QNetworkReply *reply);

private:
    QSslConfiguration m_sslConfig;
    QNetworkReply *m_reply;
};

#endif // HTTPMANAGER_H
