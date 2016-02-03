#include "keyboardplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeyBoardPlayer w;
    w.show();

    return a.exec();
}
