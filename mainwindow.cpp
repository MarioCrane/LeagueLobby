#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "version.h"
#include <QMessageBox>
#include <QDebug>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* UI */
    this->setWindowTitle("League Lobby");
    ui->statusbar->setVisible(false);
    showQueuesWidget();

    showAboutDialog();

    connect(ui->action_about, &QAction::triggered, this, &MainWindow::showAboutDialog);

    /*connect(ui->comboBox, QOverload<const QString &>::of(&QComboBox::currentTextChanged), this, [=] (QString text) {
        qDebug() << text;
    });*/
    connect(ui->cbox_paths, &QComboBox::currentTextChanged, this, [=] () {
        initSummonerInfo();
    });
    // refresh progress path
    connect(ui->btn_refresh, &QPushButton::clicked, this, &MainWindow::onRefresh);
    onRefresh();

    initSummonerInfo();

    m_lockfileReader = new LockFileReader;
    m_lobbyManager = new LobbyManager;
    connect(m_lobbyManager, &LobbyManager::result, this, &MainWindow::onResult);
    connect(m_lobbyManager, &LobbyManager::summonerInfo, this, &MainWindow::onSummonerInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRefresh()
{
    ui->cbox_paths->clear();
    auto pathList = GetProcessFullPaths("LeagueClient.exe");
    ui->cbox_paths->addItems(pathList);
}

void MainWindow::onResult(const QString &result)
{
    ui->textEdit_result->setPlainText(result);
}

void MainWindow::onSummonerInfo(const SummonerInfo &info)
{
    m_summonerInfo = info;
    if (info.name.isEmpty()) {
        m_summonerInfo.name = "未知";
        m_summonerInfo.level = 0;
        m_summonerInfo.xp = 0;
        m_summonerInfo.nextXp = 0;
        QMessageBox::critical(this, "错误!", "未能获取到正确的召唤师信息，请联系作者！");
    }
    ui->lbl_name->setText(m_summonerInfo.name);
    ui->lbl_level->setText(QString::number(m_summonerInfo.level));
    ui->lbl_xp->setText(QString("%1 / %2").arg(m_summonerInfo.xp).arg(m_summonerInfo.nextXp));
}

void MainWindow::showAboutDialog()
{
    QMessageBox::about(nullptr, "声明",
                       QString("<p>"
                       "<span style=\"font-size:26px;color:gray\">League Lobby</span>"
                       "<span style=\"color:gray\"> %1</span><br/><br/>"
                       "<span style=\"font-size:17px\">此软件为英雄联盟自定义房间工具.</span><br/>"
                       "<span style=\"font-size:17px\">此软件的开发完全遵循Riot开发者协议.</span><br/>"
                       "<span style=\"font-size:17px\">所实现的效果皆为调用Riot League of Legends开放API.</span><br/>"
                       "<span style=\"font-size:17px\">此软件</span><span style=\"font-size:20px;color:red\">不对游戏进行任何修改(内存、文件等)</span>.<br/>"
                       "<span style=\"font-size:17px\">此软件</span><span style=\"font-size:20px;color:red\">仅供学习，严禁出售！</span><br/>"
                       "<span style=\"font-size:17px\">如有任何问题请联系作者.</span><br/>"
                       "<span style=\"font-size:17px\">Bilibili UID:14671179.</span><br/>"
                       "<span style=\"font-size:17px\">交流群 %2</span><br/>"
                       "<span style=\"font-size:17px\"> 测试人员: 蓝色奇诺比奥.</span><br/>"
                       "<span style=\"font-size:17px\"> 作者: Mario.</span>"
                       "</p>").arg(LeagueLobbyVersion).arg(QQGroupId));
}


void MainWindow::on_btn_getSummonerInfo_clicked()
{
    QString path = ui->cbox_paths->currentText();
    if (path.isEmpty()) {
        QMessageBox::warning(this, "警告!", "请先开启游戏再获取召唤师信息！");
        return;
    }
    path = path.left(path.length() - QString("/LeagueClient.exe").length());
    if (m_lockfileReader->setGamePath(path)) {
        m_lobbyManager->setLoginKey(m_lockfileReader->getPort(), m_lockfileReader->getToken());
    }
    m_lobbyManager->getSummonerInfo();
}

void MainWindow::on_btn_createFromJson_clicked()
{
    if (!checkSummonerID()) {
        return;
    }

	m_lobbyManager->createLobbyFromJson(ui->textEdit_json->toPlainText());
}

void MainWindow::on_btn_createFromQueueId_clicked()
{
    if (!checkSummonerID()) {
        return;
    }

    quint16 id = static_cast<quint16>(ui->sbox_queueId->value());
    m_lobbyManager->createLobbyFromQueueId(id);

    switch (ui->cbox_increment->currentIndex()) {
    case 1:
        ui->sbox_queueId->setValue(id + 1);
        break;
    case 2:
        ui->sbox_queueId->setValue(id + 10);
        break;
    default:
        break;
    }
    ui->lbl_currentId->setText(QString::number(id));
}

void MainWindow::on_btn_create5V5Tutorial_clicked()
{
    if (!checkSummonerID()) {
        return;
    }

    qsrand(time(NULL));
    int n = qrand() % 65535;
    QString name = QString("Mario LeagueLobby 5V5 PRACTICETOOL-%1").arg(n);
    m_lobbyManager->create5V5Practice(name);
}

void MainWindow::initSummonerInfo()
{
    m_summonerInfo.name = "未知";
    onSummonerInfo(m_summonerInfo);
}

bool MainWindow::checkSummonerID()
{
    if (m_summonerInfo.id == 0) {
        QMessageBox::warning(this, "警告!", "请先获取召唤师信息在进行创建！");
        return false;
    }
    return true;
}

void MainWindow::showQueuesWidget()
{
    ui->widget_queues->setFixedWidth(200);

    QList<QueuesPair> normalQueuesPairs;
    normalQueuesPairs.append(QueuesPair("匹配模式 征召", 400));
    normalQueuesPairs.append(QueuesPair("匹配模式 自选", 420));
    normalQueuesPairs.append(QueuesPair("排位赛 单排/双排", 430));
    normalQueuesPairs.append(QueuesPair("排位赛 灵活排位", 440));
    normalQueuesPairs.append(QueuesPair("极地大乱斗", 450));
    normalQueuesPairs.append(QueuesPair("冠军杯赛 征召", 700));
    normalQueuesPairs.append(QueuesPair("人机 入门", 830));
    normalQueuesPairs.append(QueuesPair("人机 新手", 840));
    normalQueuesPairs.append(QueuesPair("人机 一般", 850));
    normalQueuesPairs.append(QueuesPair("云顶之弈 匹配", 1090));
    normalQueuesPairs.append(QueuesPair("云顶之弈 排位", 1100));
    normalQueuesPairs.append(QueuesPair("云顶之弈 教学", 1110));
    normalQueuesPairs.append(QueuesPair("新手教程 一", 2000));
    normalQueuesPairs.append(QueuesPair("新手教程 二", 2010));
    normalQueuesPairs.append(QueuesPair("新手教程 三", 2020));

    QList<QueuesPair> specialQueuesPairs;
    specialQueuesPairs.append(QueuesPair("红月决", 600));
    specialQueuesPairs.append(QueuesPair("暗星", 610));
    specialQueuesPairs.append(QueuesPair("极地大乱斗 人机", 860));
    specialQueuesPairs.append(QueuesPair("无限火力", 900));
    specialQueuesPairs.append(QueuesPair("飞升争夺战", 910));
    specialQueuesPairs.append(QueuesPair("魄罗大乱斗", 920));
    specialQueuesPairs.append(QueuesPair("极地大乱斗 召唤师峡谷", 930));
    specialQueuesPairs.append(QueuesPair("怪兽入侵 狂袭", 990));
    specialQueuesPairs.append(QueuesPair("超频行动", 1000));
    specialQueuesPairs.append(QueuesPair("冰雪无限火力", 1010));
    specialQueuesPairs.append(QueuesPair("克隆大乱斗", 1020));
    specialQueuesPairs.append(QueuesPair("奥德赛:淬炼 入门|一星", 1030));
    specialQueuesPairs.append(QueuesPair("奥德赛:淬炼 学员|二星", 1040));
    specialQueuesPairs.append(QueuesPair("奥德赛:淬炼 组员|三星", 1050));
    specialQueuesPairs.append(QueuesPair("奥德赛:淬炼 船长|四星", 1060));
    specialQueuesPairs.append(QueuesPair("奥德赛:淬炼 狂袭|五星", 1070));
    specialQueuesPairs.append(QueuesPair("极限闪击", 1200));

    QLabel *title, *secondTitle, *labelName, *labelId;
    int index = 0;
    QGridLayout *layout;
    layout = new QGridLayout;

    // Normal
    title = new QLabel("普通模式");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("background-color: rgb(76,76,76);");

    secondTitle = new QLabel("ID");
    secondTitle->setAlignment(Qt::AlignCenter);
    secondTitle->setStyleSheet("background-color: rgb(76,76,76);");

    layout->addWidget(title, index, 0);
    layout->addWidget(secondTitle, index++, 1);

    foreach (auto pair, normalQueuesPairs) {
        labelName = new QLabel(pair.first);
        labelId = new QLabel(QString::number(pair.second));
        layout->addWidget(labelName, index, 0);
        layout->addWidget(labelId, index, 1);
        index++;
        //qDebug() << pair.first << pair.second;
    }

    // Special
    title = new QLabel("轮换游戏模式");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("background-color: rgb(76,76,76);");

    secondTitle = new QLabel("ID");
    secondTitle->setAlignment(Qt::AlignCenter);
    secondTitle->setStyleSheet("background-color: rgb(76,76,76);");

    layout->addWidget(title, index, 0);
    layout->addWidget(secondTitle, index++, 1);

    foreach (auto pair, specialQueuesPairs) {
        labelName = new QLabel(pair.first);
        labelId = new QLabel(QString::number(pair.second));
        layout->addWidget(labelName, index, 0);
        layout->addWidget(labelId, index, 1);
        index++;
        //qDebug() << pair.first << pair.second;
    }

    ui->widget_queues->setLayout(layout);
    //ui->widget_queues->setVisible(true);
}
