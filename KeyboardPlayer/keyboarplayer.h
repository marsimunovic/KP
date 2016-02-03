#ifndef KEYBOARPLAYER_H
#define KEYBOARPLAYER_H

#include <QMainWindow>
#include "pianoscene.h"

namespace Ui {
class KeyBoarPlayer;
}

class KeyBoarPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit KeyBoarPlayer(QWidget *parent = 0);
    ~KeyBoarPlayer();

private:
    Ui::KeyBoarPlayer *ui;
};

#endif // KEYBOARPLAYER_H
