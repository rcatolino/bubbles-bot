#-------------------------------------------------
#
# Project created by QtCreator 2012-04-02T20:13:03
#
#-------------------------------------------------

QT       += core \
         += network

#QT       -= gui

TARGET = bubble-bot
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    networkclient.cpp \
    model.cpp \
    player.cpp \
    obstacles.cpp \
    bullet.cpp \
    actor.cpp \
    gameapp.cpp

HEADERS += \
    networkclient.h \
    model.h \
    player.h \
    obstacles.h \
    bullet.h \
    actor.h \
    gameapp.h

unix|win32: LIBS += -lqjson
