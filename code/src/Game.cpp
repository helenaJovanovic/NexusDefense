#include <code/include/Game.hpp>
#include <code/include/MapTile.hpp>
#include <QDebug>

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

void Game::initScreen() {
    scene = new QGraphicsScene();
    scene->setSceneRect(-sceneWidth/2, -sceneWidth/2, sceneWidth, sceneWidth);

    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //view->setDragMode(QGraphicsView::ScrollHandDrag);

    view->setMaximumSize(width, height);
    view->setMinimumSize(width, height);
    //view->centerOn(0, 0);

    view->show();
    qDebug() << "Screen initialized.";
}

void Game::initMap() {
    for (int i = 0; i < mapXLength; ++i) {
        for(int j = 0; j < mapYLength; ++j) {
            MapTile *tile = new MapTile();
            tile->setPos(-width/4 + i*tileWidth, -height/4 + j*tileWidth);
            scene->addItem(tile);
            mapTilesVector[i][j] = tile;
        }
    }
}

void Game::beginGame() {
    // Simple tests to see if map tiles are saved.

    qDebug() << "Game begins.";
    mapTilesVector[1][1]->setVisible(false);
    qDebug() << "Tile (1, 1) made invisible.";
}


