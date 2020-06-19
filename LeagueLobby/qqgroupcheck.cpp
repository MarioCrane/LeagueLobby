#include "qqgroupcheck.h"
#include "version.h"

QQGroupCheck::QQGroupCheck(QWidget *parent) : QWidget(parent)
{
	m_isPassed = false;

	this->setWindowTitle("QQ群验证");

    /* WebEngineView */
    QUrl checkUrl = QUrl(QString("https://qun.qq.com/member.html#gid=%1").arg(QQGroupId));
	m_webEngineView = new QWebEngineView;
    m_webEngineView->setUrl(checkUrl);
    m_webEngineView->load(checkUrl);

    /* PushButton */
    QPushButton *btnReload = new QPushButton("刷新");
    QObject::connect(btnReload, &QPushButton::clicked, m_webEngineView, [&]() {
        m_webEngineView->reload();;
    });
    QPushButton *btnCheck = new QPushButton("验证");
    QObject::connect(btnCheck, &QPushButton::clicked, m_webEngineView, [&]() {
		qDebug() << "button";
		/* Get plain text to check */
#if 0
        webEngineView->page()->toPlainText(resultCallback);
#else
		m_webEngineView->page()->toPlainText([&] (const QString &string) {
			//[退出]\\n\\n|\\n\\n反馈\\n\\n(\W+)\((\d+)\)
			QString strRx = QString("%1\\((%2)\\)\\W+[切换QQ群]").arg(QQGroupName).arg(QQGroupId);
			QRegExp rxlen(strRx);
			int pos = rxlen.indexIn(string);
			qDebug() << pos << string;
			if (pos > -1) {
				emit checkSuccess();
				close();
			}
			else {
				QMessageBox::critical(nullptr, "警告！", "验证失败，请重试！");
				QDesktopServices::openUrl(QUrl(QQGroupLink));
			}
        });
#endif
    });

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(btnReload);
    btnLayout->addWidget(btnCheck);

    QVBoxLayout *checkLayout = new QVBoxLayout;
    checkLayout->addWidget(m_webEngineView);
    checkLayout->addLayout(btnLayout);

    this->setLayout(checkLayout);
}

QQGroupCheck::~QQGroupCheck()
{
	m_webEngineView->deleteLater();
}
