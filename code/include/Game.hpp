#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"
#include "MapTile.hpp"
#include "GameTimer.hpp"
#include "GameScore.hpp"
#include "Gold.hpp"
#include "Health.hpp"
#include "EnemyUnit.hpp"
#include "SpriteLoader.hpp"
#include "CustomView.hpp"
#include "IngameInterface.hpp"


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QObject>
#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Game : public QObject {
    Q_OBJECT
public:
    // Returns a reference to the singleton game object
    static Game& game();

    // Pointer to the game timer
    QTimer *gameTimer;
    //GameTimer *gameTimer;
    Score *score;
    //Pointer to the gold saldo
    Gold *gold;
    //Pointer to the health
    Health *health;

    bool isPaused=false;
    bool isFinished=false;

    SpriteLoader *spriteLoader;

    //Pointer to the sound that should be played when user click on some button
    QMediaPlayer *buttonSound;

    //Pointer to the background music playlist
    QMediaPlayer *backgroundMusic;

    // All cleanup code goes in this function (aka freeing up memory etc)
    static void cleanup();

    void setApp(QApplication*);
    void launchGame();
    void initScreen();
    void initMap();
    void initGraphics();
    void beginGame();
    void menuScreen();
    void initScore();
    void initGold();
    void initHealth();
    void initIngameInterface();
    void initButtonSound();
    void initBackgroundMusic();
    void saveScore();

    QApplication* getGameApp();
    // Pointers to scene and view
    QGraphicsScene *scene;
    CustomView *view;
    IngameInterface *ingameInterface;

    QPushButton *startGameBtn;
    QPushButton *loadMapButton;
    QPushButton *exitButton;
    QPushButton *pauseButton;
    QPushButton *restartButton;
    QPushButton *resumeButton;
    QPushButton *backToMainMenuButton;
    QPushButton *tryAgainButton;
    QLineEdit *userName;

    QGraphicsPixmapItem* background_image;
    // Pointer to currently visible map
    Map *currentMap = nullptr;

    // Width and height of the view (shouldn't be bigger than the scene's equivalents)
    int width = 1024;
    int height = 768;

    // The maximum size of the scene
    int sceneWidth = 3200;
    int sceneHeight = 3200;

    int tileWidth = 32;
    int towerSelected = -1;
    int elapsedSpawnTime = 0;

    //Check if given X,Y is a Tower tile
    bool isTowerTile(QPointF posXY);

public slots:
    void startSecondScene();
    void startThirdScene();
    void yesOrNoQuit();
    void playButtonSound();
    void spawnWave();
    void pause();
    void restart();
    void resume();
    void onNexusDead();
    void quitGame();
    void backToMainMenu();
    void backToSecondScene();


    //TOWER SLOTS
    void setTower1();
    void setTower2();
    void setTower3();
    void setTower4();

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

    QString mapChoice = ":/mapPrototype.txt";

    int unitsSpawned = 1;



};

#endif // GAME_HPP
