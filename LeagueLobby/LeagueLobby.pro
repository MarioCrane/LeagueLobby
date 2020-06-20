QT       += core gui network #webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    httpmanager.cpp \
    lobbymanager.cpp \
    lockfilereader.cpp \
    main.cpp \
    mainwindow.cpp \
    #qqgroupcheck.cpp \
    queuesinfo.cpp

HEADERS += \
    httpmanager.h \
    lobbymanager.h \
    lockfilereader.h \
    mainwindow.h \
    processinfo.h \
    #qqgroupcheck.h \
    queues.h \
    queuesinfo.h \
    version.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    res.qrc

LIBS += -lPsapi

VERSION = 1.1.0
QMAKE_TARGET_PRODUCT = League Lobby
QMAKE_TARGET_COMPANY = MarioStudio
QMAKE_TARGET_DESCRIPTION = League Lobby
QMAKE_TARGET_COPYRIGHT = 2020 Mario. All Rights Reserved.

RC_ICONS = LeagueLobby.ico

#QMAKE_CXXFLAGS_RELEASE += -O        # Release -O
#QMAKE_CXXFLAGS_RELEASE += -O1       # Release -O1
#QMAKE_CXXFLAGS_RELEASE += -O2       # Release -O2
QMAKE_CXXFLAGS_RELEASE += -O3       # Release -O3
