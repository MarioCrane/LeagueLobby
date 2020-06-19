#ifndef QQGROUPCHECK_H
#define QQGROUPCHECK_H

/**
* @projectName   LeagueLobby
* @brief         QQ群验证，未能想到较好的方法，所以此方法实现的方式很土
* @author        Mario
* @date          2020-06-19
*/

#include <QObject>
#include <QWidget>
#include <qwebengineview.h>
#include <qwebenginepage.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qdesktopservices.h>
#include <qdebug.h>

class QQGroupCheck : public QWidget
{
    Q_OBJECT
public:
    explicit QQGroupCheck(QWidget *parent = nullptr);
	~QQGroupCheck();

signals:
    void checkSuccess();

private:
	bool m_isPassed;
	QWebEngineView *m_webEngineView;
};

#endif // QQGROUPCHECK_H
