#ifndef HTTPSMANAGER_H
#define HTTPSMANAGER_H

#include <QString>
#include <curl/curl.h>

class HttpsManager
{
public:
    HttpsManager();
    ~HttpsManager();

    QByteArray post(const QString &url, const QString &data);
    QByteArray post(const std::string &url, const std::string &data);

    QByteArray get(const QString &url);
    QByteArray get(const std::string &url);

    QByteArray patch(const QString &url, const QString &data);
    QByteArray patch(const std::string &url, const std::string &data);

private:
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
    CURLcode perform();

private:
    CURL *m_curl;
    QByteArray m_resultData;
    struct curl_slist* m_headers = NULL;
};

#endif // HTTPSMANAGER_H
