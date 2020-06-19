/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_setUID;
    QAction *action_about;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *cbox_paths;
    QPushButton *btn_refresh;
    QGroupBox *gbox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_getSummonerInfo;
    QLabel *lbl_title_name;
    QLabel *lbl_name;
    QLabel *lbl_title_level;
    QLabel *lbl_level;
    QLabel *lbl_title_xp;
    QLabel *lbl_xp;
    QSpacerItem *horizontalSpacer;
    QPlainTextEdit *textEdit_json;
    QPlainTextEdit *textEdit_result;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_createFromJson;
    QPushButton *btn_create5V5Tutorial;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QSpinBox *sbox_queueId;
    QComboBox *cbox_increment;
    QLabel *lbl_currentId;
    QLabel *lbl_title_currentId;
    QLabel *lbl_title_queueId;
    QPushButton *btn_createFromQueueId;
    QWidget *widget_queues;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(850, 630);
        action_setUID = new QAction(MainWindow);
        action_setUID->setObjectName(QString::fromUtf8("action_setUID"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QString::fromUtf8("action_about"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_5 = new QHBoxLayout(centralwidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cbox_paths = new QComboBox(centralwidget);
        cbox_paths->setObjectName(QString::fromUtf8("cbox_paths"));

        horizontalLayout->addWidget(cbox_paths);

        btn_refresh = new QPushButton(centralwidget);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_refresh->sizePolicy().hasHeightForWidth());
        btn_refresh->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(btn_refresh);


        verticalLayout_2->addLayout(horizontalLayout);

        gbox = new QGroupBox(centralwidget);
        gbox->setObjectName(QString::fromUtf8("gbox"));
        verticalLayout = new QVBoxLayout(gbox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btn_getSummonerInfo = new QPushButton(gbox);
        btn_getSummonerInfo->setObjectName(QString::fromUtf8("btn_getSummonerInfo"));

        horizontalLayout_3->addWidget(btn_getSummonerInfo);

        lbl_title_name = new QLabel(gbox);
        lbl_title_name->setObjectName(QString::fromUtf8("lbl_title_name"));

        horizontalLayout_3->addWidget(lbl_title_name);

        lbl_name = new QLabel(gbox);
        lbl_name->setObjectName(QString::fromUtf8("lbl_name"));
        lbl_name->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lbl_name);

        lbl_title_level = new QLabel(gbox);
        lbl_title_level->setObjectName(QString::fromUtf8("lbl_title_level"));

        horizontalLayout_3->addWidget(lbl_title_level);

        lbl_level = new QLabel(gbox);
        lbl_level->setObjectName(QString::fromUtf8("lbl_level"));
        lbl_level->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lbl_level);

        lbl_title_xp = new QLabel(gbox);
        lbl_title_xp->setObjectName(QString::fromUtf8("lbl_title_xp"));

        horizontalLayout_3->addWidget(lbl_title_xp);

        lbl_xp = new QLabel(gbox);
        lbl_xp->setObjectName(QString::fromUtf8("lbl_xp"));
        lbl_xp->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lbl_xp);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        textEdit_json = new QPlainTextEdit(gbox);
        textEdit_json->setObjectName(QString::fromUtf8("textEdit_json"));

        verticalLayout->addWidget(textEdit_json);

        textEdit_result = new QPlainTextEdit(gbox);
        textEdit_result->setObjectName(QString::fromUtf8("textEdit_result"));
        textEdit_result->setReadOnly(true);

        verticalLayout->addWidget(textEdit_result);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btn_createFromJson = new QPushButton(gbox);
        btn_createFromJson->setObjectName(QString::fromUtf8("btn_createFromJson"));

        horizontalLayout_2->addWidget(btn_createFromJson);

        btn_create5V5Tutorial = new QPushButton(gbox);
        btn_create5V5Tutorial->setObjectName(QString::fromUtf8("btn_create5V5Tutorial"));

        horizontalLayout_2->addWidget(btn_create5V5Tutorial);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sbox_queueId = new QSpinBox(gbox);
        sbox_queueId->setObjectName(QString::fromUtf8("sbox_queueId"));
        sbox_queueId->setMaximum(10000);

        gridLayout->addWidget(sbox_queueId, 0, 1, 1, 2);

        cbox_increment = new QComboBox(gbox);
        cbox_increment->addItem(QString());
        cbox_increment->addItem(QString());
        cbox_increment->addItem(QString());
        cbox_increment->setObjectName(QString::fromUtf8("cbox_increment"));

        gridLayout->addWidget(cbox_increment, 0, 3, 1, 1);

        lbl_currentId = new QLabel(gbox);
        lbl_currentId->setObjectName(QString::fromUtf8("lbl_currentId"));
        lbl_currentId->setMinimumSize(QSize(40, 0));
        lbl_currentId->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl_currentId, 0, 5, 1, 1);

        lbl_title_currentId = new QLabel(gbox);
        lbl_title_currentId->setObjectName(QString::fromUtf8("lbl_title_currentId"));

        gridLayout->addWidget(lbl_title_currentId, 0, 4, 1, 1);

        lbl_title_queueId = new QLabel(gbox);
        lbl_title_queueId->setObjectName(QString::fromUtf8("lbl_title_queueId"));

        gridLayout->addWidget(lbl_title_queueId, 0, 0, 1, 1);

        btn_createFromQueueId = new QPushButton(gbox);
        btn_createFromQueueId->setObjectName(QString::fromUtf8("btn_createFromQueueId"));

        gridLayout->addWidget(btn_createFromQueueId, 1, 0, 1, 6);


        horizontalLayout_2->addLayout(gridLayout);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(gbox);


        horizontalLayout_5->addLayout(verticalLayout_2);

        widget_queues = new QWidget(centralwidget);
        widget_queues->setObjectName(QString::fromUtf8("widget_queues"));

        horizontalLayout_5->addWidget(widget_queues);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 850, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(action_setUID);
        menu->addSeparator();
        menu->addAction(action_about);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_setUID->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245UID", nullptr));
        action_about->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        btn_refresh->setText(QString());
        gbox->setTitle(QCoreApplication::translate("MainWindow", "\345\237\272\347\241\200\345\212\237\350\203\275", nullptr));
        btn_getSummonerInfo->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\345\217\254\345\224\244\345\270\210\344\277\241\346\201\257", nullptr));
        lbl_title_name->setText(QCoreApplication::translate("MainWindow", "\345\220\215\345\255\227:", nullptr));
        lbl_name->setText(QCoreApplication::translate("MainWindow", "\346\234\252\347\237\245", nullptr));
        lbl_title_level->setText(QCoreApplication::translate("MainWindow", "\347\255\211\347\272\247:", nullptr));
        lbl_level->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lbl_title_xp->setText(QCoreApplication::translate("MainWindow", "\347\273\217\351\252\214:", nullptr));
        lbl_xp->setText(QCoreApplication::translate("MainWindow", "0 / 0", nullptr));
        btn_createFromJson->setText(QCoreApplication::translate("MainWindow", "\346\240\271\346\215\256Json\345\210\233\345\273\272", nullptr));
        btn_create5V5Tutorial->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\2725V5\350\256\255\347\273\203\346\250\241\345\274\217", nullptr));
        cbox_increment->setItemText(0, QCoreApplication::translate("MainWindow", "\344\270\215\351\200\222\345\242\236", nullptr));
        cbox_increment->setItemText(1, QCoreApplication::translate("MainWindow", "+1", nullptr));
        cbox_increment->setItemText(2, QCoreApplication::translate("MainWindow", "+10", nullptr));

        lbl_currentId->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lbl_title_currentId->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215ID", nullptr));
        lbl_title_queueId->setText(QCoreApplication::translate("MainWindow", "QueueId", nullptr));
        btn_createFromQueueId->setText(QCoreApplication::translate("MainWindow", "\346\240\271\346\215\256ID\345\210\233\345\273\272", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
