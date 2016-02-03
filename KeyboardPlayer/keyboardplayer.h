#ifndef KEYBOARPLAYER_H
#define KEYBOARPLAYER_H

#include "pianoscene.h"
#include "ui_keyboardplayer.h"


QT_BEGIN_NAMESPACE
class QMainWindow;
class QStackedWidget;
class QWidget;
QT_END_NAMESPACE

class KeyBoardPlayer : public QMainWindow, public Ui::keyboardPlayer
{
    Q_OBJECT

public:
    explicit KeyBoardPlayer(QWidget *parent = 0);
    ~KeyBoardPlayer();

private:
    QStackedWidget *pagesWidget;
};

#endif // KEYBOARPLAYER_H
