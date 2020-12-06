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


    scene = new QGraphicsScene();
    scene->setSceneRect(-width/2, -height/2, width-50, height-50);


    QGraphicsPixmapItem* background_image = new QGraphicsPixmapItem(QPixmap(":/images/images/battleback5.png").scaled(width, height));
    background_image->setPos(-width/2-25, -height/2-25);
    scene->addItem(background_image);

    view = new QGraphicsView(scene);

    view->setRenderHint(QPainter::Antialiasing);

    view->setMaximumSize(width, height);
    view->setMinimumSize(width, height);
    view->centerOn(0, 0);


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





    QObject::connect(startGameBtn, SIGNAL(released()), this, SLOT(startSecondScene()));

    startGameBtn->show();
    loadMapButton->show();
    exitButton->show();

    view->show();
}

void Game::startSecondScene(){
   //view->hide();
   startGameBtn->hide();
   loadMapButton->hide();
   exitButton->hide();
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


