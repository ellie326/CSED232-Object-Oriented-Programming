#include <QApplication>
#include <QFile>
#include <QTextStream>

#include "gameui.h"
#include "board.h"
#include "mainwindow.h"
#include "game.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game g;
    GameUi gameUi(g);
    g.start_the_game();
    gameUi.updateUi(g.get_board());
    gameUi.show();

    return a.exec();
}
