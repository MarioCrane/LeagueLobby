#include "mainwindow.h"
#include <QApplication>
#include "version.h"
#include <QFile>
#include <QMessageBox>
#include <qqgroupcheck.h>

#if 0
void webResultCallback(const QString &string)
{
	//[退出]\\n\\n|\\n\\n反馈\\n\\n(\W+)\((\d+)\)
	QString strRx = QString("%1\\((%2)\\)\\W+[切换QQ群]").arg(QQGroupName).arg(QQGroupId);
	QRegExp rxlen(strRx);
	if (rxlen.indexIn(string)) {
		checkWidget->close();
		checkWidget->deleteLater();
		checkWidget = NULL;
		delete checkWidget;

		// 创建主窗口
		MainWindow w;
		w.show();
	} else {
		QMessageBox::critical(nullptr, "警告！", "验证失败，请重试！");
	}
}
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/resources/Dark.qss");
    qss.open(QIODevice::ReadOnly);
    a.setStyleSheet(qss.readAll());
    qss.close();

    a.setDesktopFileName("League Lobby");
    a.setApplicationName("League Lobby");
    a.setApplicationDisplayName("League Lobby");
    a.setApplicationVersion(QString("%1").arg(LeagueLobbyVersion));

    //判断系统是否支持OpenSSL
    if (!QSslSocket::supportsSsl()) {
        QMessageBox::critical(nullptr, "错误！", "不支持SSL，请检查支持库或安装OpenSSL！");
        return -1;
    }

	MainWindow w;
	w.hide();

	/* QQ群验证 */
    QQGroupCheck groupCheck;
	QObject::connect(&groupCheck, &QQGroupCheck::checkSuccess, &w, &QWidget::show);
	groupCheck.show();

    return a.exec();
}
