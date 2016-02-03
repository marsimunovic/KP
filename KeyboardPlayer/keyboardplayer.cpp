#include "keyboardplayer.h"
#include "videoplayer.h"

#include <QBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

KeyBoardPlayer::KeyBoardPlayer(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    //VideoPlayer *videoPlayer = new VideoPlayer();

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new VideoPlayer);
    pagesWidget->addWidget(new QPushButton);
    //pagesWidget->addWidget(new VideoPlayer);
    //setup layout
    QVBoxLayout *layout = new QVBoxLayout(mcentralWidget);
    layout->setMargin(0);
    layout->addWidget(pagesWidget);
    layout->addSpacing(5);
    QGridLayout *controllerLayout = new QGridLayout(controllerBox);
    controllerLayout->addWidget(label);
    controllerLayout->addWidget(spinBox);
    controllerLayout->addWidget(label_2);
    controllerLayout->addWidget(spinBox_2);

    QVBoxLayout *keyboardLayout = new QVBoxLayout;
    keyboardLayout->addWidget(controllerBox);
    keyboardLayout->addWidget(pianokeybd);
    pianokeybd->hide();
    layout->addLayout(keyboardLayout);

//    setLayout(layout);
}

KeyBoardPlayer::~KeyBoardPlayer()
{
}
