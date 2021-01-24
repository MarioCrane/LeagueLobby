#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

#include "helpwidget.h"
#include "httpsmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QGraphicsDropShadowEffect;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void selectGamePath();
    void getGamePath();
    QString getLobbyUrl();
    void createPracticetool();
    void createFromQueueId();

private:
    void init();
    QGraphicsDropShadowEffect* createShadow();

private:
    Ui::MainWindow *ui;

    QPointer<HelpWidget> m_helpWidget;
    HttpsManager *m_httpsManager;
};
#endif // MAINWINDOW_H
