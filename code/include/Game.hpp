#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"
#include "MapTile.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>

class Game {
public:
    // Returns a reference to the singleton game object
    static Game& game();

    void launchGame();
    void initScreen();
    void initMap();
    void beginGame();

    // Pointers to scene and view
    QGraphicsScene *scene;
    QGraphicsView *view;

    // Pointer to currently visible map
    Map *currentMap = nullptr;

    // Width and height of the view (shouldn't be bigger than the scene's equivalents)
    int width = 1024;
    int height = 768;

    // The maximum size of the scene
    int sceneWidth = 3200;
    int sceneHeight = 3200;

    int tileWidth = 32;

    // TODO: make a proper static function for instance deletion
    ~Game() {

        // Don't need to worry about scene and view, they are QObjects
        // and as such are automatically deleted when game closes
        // Release only the memory which we have to take care of
        //delete currentMap;  this is a QObject aswell atm
    }
private:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static Game *instance;
};

#endif // GAME_HPP
