#-------------------------------------------------
#
# Project created by QtCreator 2016-01-30T12:26:26
#
#-------------------------------------------------

QT       += core gui multimedia svg multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeyboardPlayer
TEMPLATE = app


SOURCES += main.cpp\
    pianoscene.cpp \
    pianokey.cpp \
    pianokeyboard.cpp \
    videoplayer.cpp \
    imageviewer.cpp \
    videowidget.cpp \
    playlistmodel.cpp \
    videoplayercontrols.cpp \
    keyboardplayer.cpp

HEADERS  += \
    pianoscene.h \
    pianokey.h \
    pianokeyboard.h \
    videoplayer.h \
    imageviewer.h \
    videowidget.h \
    playlistmodel.h \
    videoplayercontrols.h \
    keyboardplayer.h

FORMS    += \
    videoplayer.ui \
    imageviewer.ui \
    keyboardplayer.ui

RESOURCES += \
    kp.qrc
