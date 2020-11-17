#ifndef GAME_HPP
#define GAME_HPP

#include "MapTile.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>

#define MAXX 10
#define MAXY 10
#define TILEWIDTH 32

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

    MapTile *mapTilesVector[MAXX][MAXY];

    // Width and height of the view
    int width = 1024;
    int height = 768;

    // The maximum size of the scene
    int sceneWidth = 3200;
    int sceneHeight = 3200;

    // The maximum X and Y length of the game map, in tiles
    int mapXLength = MAXX;
    int mapYLength = MAXY;
    int tileWidth = TILEWIDTH;


private:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static Game *instance;
};

#endif // GAME_HPP
