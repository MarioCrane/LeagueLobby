#ifndef QUEUESINFO_H
#define QUEUESINFO_H

#include <QObject>
#include <QMap>

using QueuesMap = QMap<QString, QMap<int, bool>>;

class QueuesInfo : public QObject
{
    Q_OBJECT
public:
    explicit QueuesInfo(QObject *parent = nullptr);

    /**
     * @brief 添加一个QueueID
     * @param id 模式ID
     * @param name 模式名
     * @param isSupport 当前游戏版本是否支持
     */
    void insert(const int &id, const QString &name, bool isSupport);

    QueuesMap getMap();

signals:

private:
    QueuesMap m_queuesMap;
};

#endif // QUEUESINFO_H
