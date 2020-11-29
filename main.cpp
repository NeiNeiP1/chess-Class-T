
#include <QApplication>
#include "juego.h"

Juego *game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Juego();
    game->show();
    game->menu();
    return a.exec();
}
