#include <code/include/Game.hpp>
#include <code/include/Mapper.hpp>
#include <QDebug>
#include <QDir>

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

void Game::launchGame() {
    initScreen();
    initMap();
    beginGame();
}

// Simple screen initialization. All relevant pointers are set.
void Game::initScreen() {
    scene = new QGraphicsScene();

    // This line makes the scene coordinate system -1600 -> 1600 on both axes
    scene->setSceneRect(-sceneWidth/2, -sceneWidth/2, sceneWidth, sceneWidth);

    view = new QGraphicsView(scene);
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


//
void Game::beginGame() {
    // Simple tests for now

    qDebug() << "Game begins.";
}


