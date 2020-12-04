#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"
#include "MapTile.hpp"
#include "GameTimer.hpp"
#include "GameScore.hpp"
#include "EnemyUnit.hpp"
#include "SpriteLoader.hpp"
#include "CustomView.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QObject>
#include <QApplication>

class Game : public QObject {
    Q_OBJECT
public:
    // Returns a reference to the singleton game object
    static Game& game();

    // Pointer to the game timer
    GameTimer *gameTimer;
    Score *score;
    SpriteLoader *spriteLoader;

    // All cleanup code goes in this function (aka freeing up memory etc)
    static void cleanup();

    void setApp(QApplication*);
    void launchGame();
    void initScreen();
    void initMap();
    void initGraphics();
    void initScore();

    void beginGame();

    void menuScreen();


    QApplication* getGameApp();

    // Pointers to scene and view
    QGraphicsScene *scene;
    CustomView *view;
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

        // Don't need to worry about scene and view, they are QObjects
        // and as such are automatically deleted when game closes
        // Release only the memory which we have to take care of
        //delete currentMap;  this is a QObject aswell atm

private:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    QApplication* gameApp;

    static Game *instance;

};

#endif // GAME_HPP
