#-------------------------------------------------
#
# Project created by QtCreator 2016-01-30T12:26:26
#
#-------------------------------------------------

QT       += core gui multimedia svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeyboardPlayer
TEMPLATE = app


SOURCES += main.cpp\
        keyboarplayer.cpp \
    pianoscene.cpp \
    pianokey.cpp \
    pianokeyboard.cpp

HEADERS  += keyboarplayer.h \
    pianoscene.h \
    pianokey.h \
    pianokeyboard.h

FORMS    += keyboarplayer.ui

RESOURCES += \
    kp.qrc
