#include <QApplication>

#include <code/include/Game.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game& game = Game::game();
    game.launchGame();

    return a.exec();
}
