QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += CURL_STATICLIB

SOURCES += \
    gameinfo.cpp \
    helpwidget.cpp \
    httpsmanager.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    gameinfo.h \
    helpwidget.h \
    httpsmanager.h \
    mainwindow.h \
    stylesheet.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

#LIBS += ws2_32.lib winmm.lib wldap32.lib Crypt32.lib Normaliz.lib
LIBS += -L$$PWD/libs/lib/ -llibcurl_a
PRE_TARGETDEPS += $$PWD/libs/lib/libcurl_a.lib
INCLUDEPATH += $$PWD/libs/include
DEPENDPATH += $$PWD/libs/include

VERSION = 1.0.0.0
RC_ICONS = LeagueLobby.ico
QMAKE_TARGET_PRODUCT = League Lobby
QMAKE_TARGET_COMPANY = Mario
QMAKE_TARGET_DESCRIPTION = League Lobby
QMAKE_TARGET_COPYRIGHT = Mario

QMAKE_CXXFLAGS_RELEASE = -O2
