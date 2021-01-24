#include "httpsmanager.h"
#include <QDebug>

#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "Crypt32.lib")

HttpsManager::HttpsManager()
{
    m_curl = curl_easy_init();

    // SSL
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0);

    // Header
    m_headers = curl_slist_append(m_headers, "Expect:");
    m_headers = curl_slist_append(m_headers, "Content-Type: application/json");
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers);

    // Callback
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_resultData);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeCallback);
}

HttpsManager::~HttpsManager()
{
    curl_slist_free_all(m_headers);
    curl_easy_cleanup(m_curl);
}

QByteArray HttpsManager::post(const QString &url, const QString &data)
{
    return post(url.toStdString(), data.toStdString());
}

QByteArray HttpsManager::post(const std::string &url, const std::string &data)
{
    curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data.c_str());

    if (perform() == CURLE_OK) {
        return m_resultData;
    }
    return "";
}

QByteArray HttpsManager::get(const QString &url)
{
    return get(url.toStdString());
}

QByteArray HttpsManager::get(const std::string & url)
{
    curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

    if (perform() == CURLE_OK) {
        return m_resultData;
    }
    return "";
}

QByteArray HttpsManager::patch(const QString &url, const QString &data)
{
    return patch(url.toStdString(), data.toStdString());
}

QByteArray HttpsManager::patch(const std::string & url, const std::string & data)
{
    curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data.c_str());

    if (perform() == CURLE_OK) {
        return m_resultData;
    }
    return "";
}

size_t HttpsManager::writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    auto len = size * nmemb;
    QByteArray *replyData = (QByteArray *)userp;
    replyData->append((char*)contents, static_cast<int>(len));

    return len;
}

CURLcode HttpsManager::perform()
{
    CURLcode res = curl_easy_perform(m_curl);
    if (res != CURLE_OK) {
        qDebug() << "curl failed:" << curl_easy_strerror(res);
    }
    return res;
}
