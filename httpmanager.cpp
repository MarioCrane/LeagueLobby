#include "httpmanager.h"
#include <QDebug>

HttpManager::HttpManager()
{
    // Check SSL
    m_sslConfig = QSslConfiguration::defaultConfiguration();
    m_sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    m_sslConfig.setProtocol(QSsl::TlsV1_2);

    connect(this, SIGNAL(finished(QNetworkReply *)), this, SLOT(onReplyFinished(QNetworkReply *)));
}

HttpManager::~HttpManager()
{
}

/////////////// PUBLIC FUNCTIONS ///////////////
QNetworkReply *HttpManager::postRequest(const QString &url, const QString &strRequest)
{
    // Message Head
    QNetworkRequest request;
    request.setSslConfiguration(m_sslConfig);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(QUrl(url));

    m_reply = post(request, strRequest.toLatin1());

    return m_reply;
}

QNetworkReply *HttpManager::getRequest(const QString &url)
{
    // Message Head
    QNetworkRequest request;
    request.setSslConfiguration(m_sslConfig);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(QUrl(url));

    m_reply = get(request);

    return m_reply;
}

/////////////// PRIVATE SLOTS ///////////////
void HttpManager::onReplyFinished(QNetworkReply *reply)
{
    // Get reply string then abort it.
    QByteArray bytes = reply->readAll();

    reply->abort();
    reply->close();
    reply->deleteLater();
    reply = NULL;

    QString resultStr = bytes;
    qDebug() << resultStr;
    emit result(resultStr);
}
