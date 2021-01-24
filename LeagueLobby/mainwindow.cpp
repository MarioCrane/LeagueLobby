#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stylesheet.h"
#include "gameinfo.h"

#include <QPointer>
#include <QGraphicsDropShadowEffect>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>

const QString ProcessName = "LeagueClient.exe";
const QString SummonerUrl = "https://riot:%1@127.0.0.1:%2/lol-summoner/v1/current-summoner";
const QString LobbyUrl = "https://riot:%1@127.0.0.1:%2/lol-lobby/v2/lobby";

const QString JsonPracticetool = R"(
{
    "customGameLobby": {
        "configuration": {
            "gameMode": "PRACTICETOOL",
            "gameMutator": "",
            "gameServerRegion": "",
            "mapId": 11,
            "mutators": {
                "id": 1
            },
            "spectatorPolicy": "AllAllowed",
            "teamSize": 5
       },
       "lobbyName": "LeagueLobby 5V5 PRACTICETOOL-%1",
       "lobbyPassword": null
    },
    "isCustom": true
}
)";
const QString JsonQueueId = R"({"queueId": %1})";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_helpWidget(new HelpWidget)
    , m_httpsManager(new HttpsManager)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete m_httpsManager;
    delete ui;
}

void MainWindow::selectGamePath()
{
    QString gamePath;
    QPointer<QFileDialog> dialog(new QFileDialog(this));
    dialog->setWindowTitle(QString("Select %1").arg(ProcessName));
    dialog->setDirectory(qApp->applicationDirPath());
    dialog->setNameFilter(QString("%1 (%1)").arg(ProcessName));
    dialog->setViewMode(QFileDialog::Detail);
    if (dialog->exec() == QDialog::Accepted) {
        gamePath = dialog->selectedFiles().first();
        gamePath.remove(ProcessName);
        ui->edit_path->setText(gamePath);
    }
}

void MainWindow::getGamePath()
{
    auto gamePath = GameInfo::getGamePath();
    if (gamePath.isEmpty()) {
        QMessageBox::warning(this, "Failed!", "Can't get game path!");
        return;
    }
    ui->edit_path->setText(gamePath);
}

QString MainWindow::getLobbyUrl()
{
    QString url;
    auto gamePath = ui->edit_path->text();
    if (gamePath.isEmpty()) {
        QMessageBox::warning(this, "Failed!", "Please set game path!");
        return url;
    }

    auto lockfile = GameInfo::getLockFile(gamePath);
    if (lockfile.port.isEmpty() || lockfile.token.isEmpty()) {
        QMessageBox::warning(this, "Failed!", "Can't read lockfile!");
        return url;
    }

    url = LobbyUrl.arg(lockfile.token).arg(lockfile.port);
    return url;
}

void MainWindow::createPracticetool()
{
    auto lobbyUrl = getLobbyUrl();
    if (!lobbyUrl.isEmpty())
        m_httpsManager->post(lobbyUrl, JsonPracticetool.arg(qrand() % 65535).simplified());
}

void MainWindow::createFromQueueId()
{
    auto lobbyUrl = getLobbyUrl();
    if (!lobbyUrl.isEmpty())
        m_httpsManager->post(lobbyUrl, JsonQueueId.arg(ui->edit_queueId->text()));
}

void MainWindow::init()
{
    // MainWindow
    setFixedSize(width(), height());
    setWindowTitle("League Lobby");

    // Stylesheet
    this->setStyleSheet(WidgetStyleSheet + ButtonStyleSheet +
                        LineEditStyleSheet + ToolTipStyleSheet);
    ui->btn_help_practicetool->setStyleSheet(HelpStyleSheet);
    ui->btn_help_queueId->setStyleSheet(HelpStyleSheet);
    ui->btn_refresh->setStyleSheet(RefreshStyleSheet);

    // Shadow
    ui->btn_select->setGraphicsEffect(createShadow());
    ui->btn_refresh->setGraphicsEffect(createShadow());
    ui->btn_create_practicetool->setGraphicsEffect(createShadow());
    ui->btn_create_queueId->setGraphicsEffect(createShadow());
    ui->btn_help_practicetool->setGraphicsEffect(createShadow());
    ui->btn_help_queueId->setGraphicsEffect(createShadow());
    ui->edit_path->setGraphicsEffect(createShadow());
    ui->edit_queueId->setGraphicsEffect(createShadow());

    // ToolTip
    ui->btn_help_practicetool->setToolTip("Create 5v5 practicetool.\nClick to view details.");
    ui->btn_help_queueId->setToolTip("Create lobby from queueId.\nClick to view details.");

    // Title
    ui->btn_select->setText("...");
    ui->btn_create_practicetool->setText("Create 5v5 practicetool");
    ui->btn_create_queueId->setText("Create");
    ui->label_source_link->setText("<a style='color: green;' href = github.com>github.com/MarioCrane</a>");

    // Edit
    ui->edit_path->setPlaceholderText(QString("%1 Path").arg(ProcessName));
    ui->edit_path->setReadOnly(true);
    ui->edit_queueId->setText("1091");
    ui->edit_queueId->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));

    // Slots
    connect(ui->btn_help_practicetool, &QPushButton::clicked, this, [=] () {
        auto lobbyUrl = getLobbyUrl();
        if (!lobbyUrl.isEmpty())
            m_helpWidget->showHelp(getLobbyUrl(), "post\n" + JsonPracticetool.arg(qrand() % 65535));
    });
    connect(ui->btn_help_queueId, &QPushButton::clicked, this, [=] () {
        auto lobbyUrl = getLobbyUrl();
        if (!lobbyUrl.isEmpty())
            m_helpWidget->showHelp(getLobbyUrl(), "post\n" + JsonQueueId.arg(ui->edit_queueId->text()));
    });

    connect(ui->btn_select, &QPushButton::clicked, this, &MainWindow::selectGamePath);
    connect(ui->btn_refresh, &QPushButton::clicked, this, &MainWindow::getGamePath);
    connect(ui->btn_create_practicetool, &QPushButton::clicked, this, &MainWindow::createPracticetool);
    connect(ui->btn_create_queueId, &QPushButton::clicked, this, &MainWindow::createFromQueueId);

    connect(ui->label_source_link, &QLabel::linkActivated, this, [=] () {
        QDesktopServices::openUrl(QUrl("https://github.com/MarioCrane/LeaueLobby"));
    });
}

QGraphicsDropShadowEffect *MainWindow::createShadow()
{
    QPointer<QGraphicsDropShadowEffect> shadow(new QGraphicsDropShadowEffect);
    shadow->setBlurRadius(15);
    shadow->setOffset(1);
    shadow->setColor(Qt::gray);
    return shadow.data();
}
