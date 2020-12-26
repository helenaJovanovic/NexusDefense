#include <code/include/Game.hpp>
#include <code/include/Mapper.hpp>
#include <code/include/Tower.hpp>

#include <QDebug>
#include <QDir>
#include <QGLWidget>
#include <QPointer>
#include <QObject>
#include <QScreen>
#include <QMediaPlayer>
#include <QFileDialog>

#include <code/include/Bat.hpp>
#include <code/include/Skeleton.hpp>
#include <code/include/Vampire.hpp>


Game *Game::instance = 0;

Game::Game() {
    //qDebug() << "Constructor called.";
}

Game &Game::game()
{
    if(!instance)
        instance = new Game();
    return *instance;
}

void Game::menuScreen(){
    //Add a smaller scene with a view to
    //show the starting menu witha button
    //Button deletes the main menu and starts the game
    //scene and view

    scene = new QGraphicsScene();
    scene->setSceneRect(-width/2, -height/2, width-50, height-50);

    background_image = new QGraphicsPixmapItem(QPixmap(":/images/images/battleback5.png").scaled(width, height));
    background_image->setPos(-width/2-25, -height/2-25);
    scene->addItem(background_image);

    view = new CustomView(scene);

    view->setMaximumSize(width, height);
    view->setMinimumSize(width, height);
    view->centerOn(0, 0);

    initButtonSound();

    startGameBtn = new QPushButton("Start Game", view);
    startGameBtn->setGeometry(QRect(QPoint(450, 300), QSize(150, 50)));
    startGameBtn->setStyleSheet(
                "QPushButton {"
                        "border-image:url(:/images/images/normal.png); min-width: 150; min-height: 50;"
                         "font: 20px Arial, sans-serif;"
                "}"
                "QPushButton:pressed {"
                        "border-image:url(:/images/images/pressed.png); min-width: 150; min-height: 50;"
                "}"
                );




    loadMapButton = new QPushButton("Change map", view);
    loadMapButton->setGeometry(QRect(QPoint(450, 375), QSize(150, 50)));
    loadMapButton->setStyleSheet(
                "QPushButton {"
                        "border-image:url(:/images/images/normal.png); min-width: 150; min-height: 50;"
                        "font: 20px Arial, sans-serif;"
                "}"
                "QPushButton:pressed {"
                        "border-image:url(:/images/images/pressed.png); min-width: 150; min-height: 50;"
                "}"
                );

    exitButton = new QPushButton("Exit", view);
    exitButton->setGeometry(QRect(QPoint(450, 450), QSize(150, 50)));
    exitButton->setStyleSheet(
                "QPushButton {"
                        "border-image:url(:/images/images/normal.png); min-width: 150; min-height: 50;"
                        "font: 20px Arial, sans-serif;"
                "}"
                "QPushButton:pressed {"
                        "border-image:url(:/images/images/pressed.png); min-width: 150; min-height: 50;"
                "}"
                );



    QObject::connect(startGameBtn, SIGNAL(clicked()), this, SLOT(playButtonSound()));
    QObject::connect(startGameBtn, SIGNAL(released()), this, SLOT(startSecondScene()));

    QObject::connect(loadMapButton, SIGNAL(clicked()), this, SLOT(playButtonSound()));
    QObject::connect(loadMapButton, SIGNAL(released()), this, SLOT(startThirdScene()));

    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(playButtonSound()));
    QObject::connect(exitButton, SIGNAL(released()), this, SLOT(localQuitGame()));

    startGameBtn->show();
    loadMapButton->show();
    exitButton->show();

    view->show();
}

void Game::localQuitGame(){
    gameApp->quit();
}

//Checking if the buttonSound is already playing
//If not then it should start playing
void Game::playButtonSound()
{
    if(buttonSound->state() == QMediaPlayer::PlayingState) {
        buttonSound->setPosition(0);
    }
    else if(buttonSound->state() == QMediaPlayer::StoppedState) {
        buttonSound->play();
    }

}

void Game::startSecondScene(){
   
   startGameBtn->hide();
   loadMapButton->hide();
   exitButton->hide();
   //scene->removeItem(background_image);
   initScreen();
   initGraphics();
   initMap();
   initScore();
   initGold();
   initHealth();
   initIngameInterface();
   initPlaylist();
   beginGame();
}

void Game::startThirdScene(){

    QString temp = QFileDialog::getOpenFileName(loadMapButton, tr("Open .txt file"), "/", tr("Text files (*.txt)"));

    if(temp != ""){
        mapChoice = temp;
    }

    //exitButton->hide();
}

void Game::setApp(QApplication *app) {
    gameApp = app;
}

QApplication *Game::getGameApp() {
    return gameApp;
}

void Game::launchGame() {
    menuScreen();
}

// Simple screen initialization. All relevant pointers are set.
void Game::initScreen() {
    scene = new QGraphicsScene();

    // This line makes the scene coordinate system -1600 -> 1600 on both axes
    scene->setSceneRect(-sceneWidth/2, -sceneWidth/2, sceneWidth, sceneWidth);
    scene->setItemIndexMethod(scene->NoIndex);
    //view = new QGraphicsView(scene);

    view->setScene(scene);
    view->setViewport(new QGLWidget());
    view->setRenderHint(QPainter::SmoothPixmapTransform);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    //view->setRenderHint(QPainter::Antialiasing);

    /* fullscreen test

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    height = screenGeometry.height();
    width = screenGeometry.width();

    view->setMaximumSize(width, height);
    view->setMinimumSize(width, height);

    view->showFullScreen();
    */
}

// chosenMap is hard-coded atm, changeable later with level selection code
void Game::initMap() {
    QString chosenMap = ":/mapSecond.txt";
    currentMap = new Map(new Mapper(chosenMap));
}

void Game::initGraphics() {
    spriteLoader = new SpriteLoader("units", "towers", "misc");
}


//
void Game::beginGame() {
    gameTimer = new QTimer(this);
    gameTimer->start(16);
    view->enableMouseMovement();

    connect(gameTimer, &QTimer::timeout, this, &Game::spawnWave);

    /*new Bat(currentMap->unitSpawnPointer->pos(), unitsSpawned++);
    new Skeleton(currentMap->unitSpawnPointer->pos(), unitsSpawned++);
    new Vampire(currentMap->unitSpawnPointer->pos(), unitsSpawned++);*/

    qDebug() << "Game begins.";

    /*   SpriteLoader example
     *
     *   Sprite* zombie = spriteLoader->getUnitSprite("Zombie");
     *   auto tmpMap = zombie->getStatesMap();
     *
     *   qDebug() << zombie->getName();
     *   qDebug() << "Duration of the first frame of the east state: "
     *            << tmpMap["east"][0].duration;
     *   qDebug() << "Second frame rectangle to draw: "
     *            << tmpMap["east"][1].rect;
     */


}

//Spawn enemies on every 16 seconds
void Game::spawnWave(){
    elapsedSpawnTime += 16;

    if(elapsedSpawnTime % 16000 == 0 || elapsedSpawnTime == 16){
		/*new EnemyUnit(currentMap->unitSpawnPointer, "Bat", 1);
        new EnemyUnit(currentMap->unitSpawnPointer, "Bat", 2);
        new EnemyUnit(currentMap->unitSpawnPointer, "Bat", 3);
        new EnemyUnit(currentMap->unitSpawnPointer, "Bat", 4);

        new EnemyUnit(currentMap->unitSpawnPointer, "Skeleton", 2);*/

        new Bat(currentMap->unitSpawnPointer->pos(), unitsSpawned++);
        new Skeleton(currentMap->unitSpawnPointer->pos(), unitsSpawned++);
        new Vampire(currentMap->unitSpawnPointer->pos(), unitsSpawned++);
	}
}

void Game::cleanup() {

    delete Game::game().spriteLoader;
    delete instance;

    qDebug() << "Game ends.";
}

void Game::initScore() {
    score = new Score();
    QPointF pos = view->mapToScene(0, 0);
    Game::game().score->setPos(pos.x(), pos.y()+40);
    scene->addItem(score);
}

void Game::initGold() {
    gold = new Gold();
    QPointF pos = view->mapToScene(0, 0);
    gold->setPos(pos.x(), pos.y());
    scene->addItem(gold);
}

void Game::initHealth() {
    health = new Health();

    QPointF pos = view->mapToScene(0, 0);
    health->setPos(pos.x(), pos.y()+20);
    scene->addItem(health);
}

void Game::initIngameInterface() {
    ingameInterface = new IngameInterface(view);
    ingameInterface->showInterface();
}

bool Game::isTowerTile(QPointF posXY){
    //Return if tower is buldable on tile

    if(currentMap->getTilePointer(static_cast<int>(posXY.x()), static_cast<int>(posXY.y()))->type == "T"
           || currentMap->getTilePointer(static_cast<int>(posXY.x()), static_cast<int>(posXY.y()))->type == "TE"){
        return true;
    }

	return false;
}

void Game::initButtonSound()
{
    buttonSound = new QMediaPlayer();
    buttonSound->setMedia(QUrl("qrc:/sounds/StoneButton.mp3"));
}

void Game::initPlaylist()
{
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/bgsound.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(20);
    music->play();

}






