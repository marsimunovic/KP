#include "keyboarplayer.h"
#include "ui_keyboarplayer.h"


KeyBoarPlayer::KeyBoarPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KeyBoarPlayer)
{
    ui->setupUi(this);
}

KeyBoarPlayer::~KeyBoarPlayer()
{
    delete ui;
}
