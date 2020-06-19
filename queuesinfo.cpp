#include "queuesinfo.h"

QueuesInfo::QueuesInfo(QObject *parent) : QObject(parent)
{
}

void QueuesInfo::insert(const int &id, const QString &name, bool isSupport)
{
    QMap<int, bool> map;
    map.insert(id, isSupport);
    m_queuesMap.insert(name, map);
}

QueuesMap QueuesInfo::getMap()
{
    return m_queuesMap;
}
