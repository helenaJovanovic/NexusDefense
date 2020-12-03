#include <code/include/Game.hpp>
#include <code/include/Mapper.hpp>
#include <code/include/SpriteLoader.hpp>
#include <QDebug>
#include <QDir>
#include <QPointer>


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

    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);

    view->setMaximumSize(width, height);
    view->setMinimumSize(width, height);
    view->centerOn(0, 0);


    startGameBtn = new QPushButton("Start Game", view);
    startGameBtn->setGeometry(QRect(QPoint(450, 320), QSize(150, 100)));


    QObject::connect(startGameBtn, SIGNAL(released()), this, SLOT(startSecondScene()));
    scene->addWidget(startGameBtn);
    startGameBtn->show();


    view->show();
}

void Game::startSecondScene(){
   //view->hide();
   delete startGameBtn;
   //delete view;
   initScreen();
   initGraphics();
   initMap();
   initScore();
   beginGame();
}

void Game::launchGame() {
    menuScreen();
}

// Simple screen initialization. All relevant pointers are set.
void Game::initScreen() {
    scene = new QGraphicsScene();

    // This line makes the scene coordinate system -1600 -> 1600 on both axes
    scene->setSceneRect(-sceneWidth/2, -sceneWidth/2, sceneWidth, sceneWidth);

    //view = new QGraphicsView(scene);
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //view->setDragMode(QGraphicsView::ScrollHandDrag);

    view->setMaximumSize(width, height);
    view->setMinimumSize(width, height);

    // Centering the scene to (0, 0), in this case, puts it in dead middle of the scene
    view->centerOn(0, 0);

    view->show();
    //qDebug() << "Screen initialized.";
}

// chosenMap is hard-coded atm, changeable later with level selection code
void Game::initMap() {
    QString chosenMap = ":/mapPrototype.txt";
    currentMap = new Map(new Mapper(chosenMap));
}

void Game::initGraphics() {
    spriteLoader = new SpriteLoader("units", "towers", "misc");
}


//
void Game::beginGame() {
    // Simple tests for now
    gameTimer = new GameTimer();
	
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

void Game::cleanup() {

    delete Game::game().spriteLoader;
    delete instance;

    qDebug() << "Game ends.";
}


void Game::initScore() {
    score = new Score();
    scene->addItem(score);
}


