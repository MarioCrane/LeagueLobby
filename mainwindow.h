#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
* @projectName   LeagueLobby
* @brief         英雄联盟自定义房间创建工具
* @author        Mario
* @date          2020-06-19
*/

#include <QMainWindow>
#include "processinfo.h"
#include "lockfilereader.h"
#include "lobbymanager.h"
//#include "queuesinfo.h"

using QueuesPair = QPair<QString, int>;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief 弹出关于对话框
     */
    void showAboutDialog();

    /**
     * @brief 刷新游戏进程
     */
    void onRefresh();

    /**
     * @brief 得到HTTP请求返回的结果
     * @param result
     */
    void onResult(const QString &result);

    /**
     * @brief 得到召唤师信息
     * @param info
     */
    void onSummonerInfo(const SummonerInfo &info);

    /**
     * @brief 获取召唤师信息
     */
    void on_btn_getSummonerInfo_clicked();

    /**
     * @brief 根据Json创建房间
     */
    void on_btn_createFromJson_clicked();

    /**
     * @brief 根据QueueId创建房间
     */
    void on_btn_createFromQueueId_clicked();

    /**
     * @brief 创建5V5训练营
     */
    void on_btn_create5V5Tutorial_clicked();

private:
    /**
     * @brief initSummonerInfo
     */
    void initSummonerInfo();

    /**
     * @brief 检查召唤师ID是否存在来判断是否获取到了召唤师信息
     * @return 返回状态，True为成功、False为失败
     */
    bool checkSummonerID();

    /**
     * @brief 显示QueueId窗口
     */
    void showQueuesWidget();

private:
    Ui::MainWindow *ui;

    LockFileReader *m_lockfileReader;
    LobbyManager *m_lobbyManager;
    SummonerInfo m_summonerInfo;
};
#endif // MAINWINDOW_H
