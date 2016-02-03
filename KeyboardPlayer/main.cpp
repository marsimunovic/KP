#include "keyboarplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeyBoarPlayer w;
    w.show();

    return a.exec();
}
