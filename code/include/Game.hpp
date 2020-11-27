#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"
#include "MapTile.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QObject>

class Game : public QObject {
    Q_OBJECT
public:
    // Returns a reference to the singleton game object
    static Game& game();

    // All cleanup code goes in this function (aka freeing up memory etc)
    static void cleanup();

    void launchGame();
    void initScreen();
    void initMap();
    void beginGame();
    void menuScreen();

    // Pointers to scene and view
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *startGameBtn;

    // Pointer to currently visible map
    Map *currentMap = nullptr;

    // Width and height of the view (shouldn't be bigger than the scene's equivalents)
    int width = 1024;
    int height = 768;

    // The maximum size of the scene
    int sceneWidth = 3200;
    int sceneHeight = 3200;

    int tileWidth = 32;

public slots:
    void startSecondScene();

private:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static Game *instance;
};

#endif // GAME_HPP
