#include <QApplication>
#include <code/include/Game.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game& game = Game::game();
    // Connect the aboutToQuit signal of the application (called when the window X button is pressed)
    // to our static cleanup function which will free all allocated memory etc.
    QObject::connect(&a, &QApplication::aboutToQuit, game.cleanup);
    game.setApp(&a);
    game.launchGame();

    return a.exec();
}
