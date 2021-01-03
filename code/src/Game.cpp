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
#include <QGraphicsTextItem>
#include <QFont>
#include <QLineEdit>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include <code/include/Bat.hpp>
#include <code/include/Skeleton.hpp>
#include <code/include/Vampire.hpp>
#include <code/include/IngameInterface.hpp>
#include <code/include/TextItem.hpp>


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
    QObject::connect(exitButton, SIGNAL(released()), this, SLOT(yesOrNoQuit()));

    startGameBtn->show();
    loadMapButton->show();
    exitButton->show();

    view->show();
}

void Game::yesOrNoQuit() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(exitButton, "Exit test","Are you sure you want to exit the game?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
     qDebug() << "Yes was clicked";
     QTimer::singleShot(200,this,SLOT(quitGame()));
    }
    else
     qDebug() << "No was clicked";
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
   initBackgroundMusic();
   beginGame();
}

void Game::startThirdScene(){

    QString temp = QFileDialog::getOpenFileName(loadMapButton, tr("Open .txt file"), "/", tr("Text files (*.txt)"));

    if(temp != ""){
        mapChoice = temp;
        QMessageBox::information(loadMapButton,"Success","The map was successfully loaded", QMessageBox::Ok,0);
    }

    QMessageBox::information(loadMapButton,"Failure", "The map was not successfully loaded", QMessageBox::Ok,0);
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

    pauseButton = new QPushButton("Pause", view);
    pauseButton->setGeometry(QRect(QPoint(850,100), QSize(150, 50)));
    pauseButton->setStyleSheet(
                "QPushButton {"
                        "border-image:url(:/images/images/normal.png); min-width: 150; min-height: 50;"
                        "font: 20px Arial, sans-serif;"
                "}"
                "QPushButton:pressed {"
                        "border-image:url(:/images/images/pressed.png); min-width: 150; min-height: 50;"
                "}"
                );


    restartButton = new QPushButton("Restart",view);
    restartButton->setGeometry(QRect(QPoint(850,150), QSize(150, 50)));
    restartButton->setStyleSheet(
                        "QPushButton {"
                                "border-image:url(:/images/images/normal.png); min-width: 150; min-height: 50;"
                                "font: 20px Arial, sans-serif;"
                        "}"
                        "QPushButton:pressed {"
                                "border-image:url(:/images/images/pressed.png); min-width: 150; min-height: 50;"
                        "}"
                        );
    resumeButton = new QPushButton("Resume", view);
    resumeButton->setGeometry(QRect(QPoint(850,100), QSize(150, 50)));
    resumeButton->setStyleSheet(
                "QPushButton {"
                        "border-image:url(:/images/images/normal.png); min-width: 150; min-height: 50;"
                        "font: 20px Arial, sans-serif;"
                "}"
                "QPushButton:pressed {"
                        "border-image:url(:/images/images/pressed.png); min-width: 150; min-height: 50;"
                "}"
                );

    QObject::connect(resumeButton,SIGNAL(clicked()), this, SLOT(playButtonSound()));
    QObject::connect(resumeButton, SIGNAL(released()), this, SLOT(resume()));


    QObject::connect(pauseButton,SIGNAL(clicked()), this, SLOT(playButtonSound()));
    QObject::connect(pauseButton, SIGNAL(released()), this, SLOT(pause()));

    QObject::connect(restartButton,SIGNAL(clicked()), this, SLOT(playButtonSound()));
    QObject::connect(restartButton, SIGNAL(released()), this, SLOT(restart()));

    pauseButton->show();
    restartButton->show();


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

        new Bat(currentMap->unitSpawnPointer->pos());
        new Skeleton(currentMap->unitSpawnPointer->pos());
        new Vampire(currentMap->unitSpawnPointer->pos());

        spriteLoader->buffEnemyUnits(2, 2);
	}
}

void Game::pause()
{
    qDebug() << "Game paused";
    ingameInterface->hideInterface();
    pauseButton->hide();
    restartButton->hide();
    backgroundMusic->pause();
    resumeButton->show();
    isPaused = !isPaused;
    gameTimer->stop();
}

void Game::restart()
{
    qDebug() << "Game restarted";
    gameTimer->stop();
    backgroundMusic->stop();
    startSecondScene();
}

void Game::resume()
{
    qDebug() << "Game resumed";
    resumeButton->hide();
    pauseButton->show();
    ingameInterface->showInterface();
    restartButton->show();
    backgroundMusic->play();
    isPaused = !isPaused;
    gameTimer->start(16);
}

void Game::onNexusDead()
{
    isFinished = true;
    gameTimer->stop();
    backgroundMusic->stop();
    ingameInterface->hideInterface();
    restartButton->hide();
    pauseButton->hide();
    int currentScore = score->getScore();
    scene = new QGraphicsScene();
    scene->setSceneRect(-width/2, -height/2, width-50, height-50);

    background_image = new QGraphicsPixmapItem(QPixmap(":/images/images/graveyard.jpeg").scaled(width, height));
    background_image->setPos(-width/2-25, -height/2-25);
    scene->addItem(background_image);

    QGraphicsTextItem *io = new QGraphicsTextItem;
    io->setPos(-150,-250);
    io->setPlainText("Your score: " + QString::number(currentScore));

    QFont f;
    f.setPointSize(28);
    f.setItalic(true);
    f.setWeight(QFont::Bold);
    f.setStyleHint(QFont::Helvetica);

    io->setFont(f);

    io->setDefaultTextColor(QColorConstants::Green);


    scene->addItem(io);

    TextItem* playerName = new TextItem();
    playerName->setPlainText("Player name");
    playerName->setPos(-200,-300);

    scene->addItem(playerName);

    view->setScene(scene);

    view->setMaximumSize(width, height);
    view->setMinimumSize(width, height);
    view->centerOn(0, 0);


    backToMainMenuButton = new QPushButton("Back to main menu", view);
    backToMainMenuButton->setGeometry(QRect(QPoint(400, 250), QSize(200, 50)));
    backToMainMenuButton->setStyleSheet(
                "QPushButton {"
                        "border-image:url(:/images/images/normal.png); min-width: 200; min-height: 50;"
                         "font: 20px Arial, sans-serif;"
                "}"
                "QPushButton:pressed {"
                        "border-image:url(:/images/images/pressed.png); min-width: 200; min-height: 50;"
                "}"
                );

    tryAgainButton = new QPushButton("Try again", view);
    tryAgainButton->setGeometry(QRect(QPoint(400, 325), QSize(200, 50)));
    tryAgainButton->setStyleSheet(
                "QPushButton {"
                        "border-image:url(:/images/images/normal.png); min-width: 200; min-height: 50;"
                         "font: 20px Arial, sans-serif;"
                "}"
                "QPushButton:pressed {"
                        "border-image:url(:/images/images/pressed.png); min-width: 200; min-height: 50;"
                "}"
                );



    QObject::connect(backToMainMenuButton, SIGNAL(clicked()), this, SLOT(playButtonSound()));
    QObject::connect(backToMainMenuButton, SIGNAL(released()), this, SLOT(backToMainMenu()));

    QObject::connect(tryAgainButton, SIGNAL(clicked()), this, SLOT(playButtonSound()));
    QObject::connect(tryAgainButton, SIGNAL(released()), this, SLOT(backToSecondScene()));

    backToMainMenuButton->show();
    tryAgainButton->show();

    view->show();
}

void Game::backToMainMenu() {
    isFinished=false;
    view->hide();
    menuScreen();
}

void Game::backToSecondScene() {
    isFinished=false;
    startSecondScene();
}

void Game::quitGame()
{
    gameApp->quit();
}

void Game::saveScore()
{
   if(game().isFinished == true) {
    qDebug() << "Saving score";
    QVector<int> scores;
    QFile file("../highscores.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        QMessageBox::information(view,"Failure","The score was not successfully saved", QMessageBox::Ok,0);
        return;
    }
    //QTextStream in(&file);
    QTextStream out(&file);

   // while(!in.atEnd()) {
   //     QString line = in.readLine();
   //     bool convertOK;
   //     int num = line.toInt(&convertOK);
   //     if(!convertOK)
   //         return;
   //     scores.push_back(num);
   // }

   // scores.push_back(score->getScore());
   // qsort(scores.begin(),scores.end());

   out << score->getScore() << endl;
   QMessageBox::information(view,"Success","The score was successfully saved", QMessageBox::Ok,0);

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

    QObject::connect(health, SIGNAL(dead()),this,SLOT(onNexusDead()));
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

void Game::initBackgroundMusic()
{
   QMediaPlaylist *playlist = new QMediaPlaylist();
   playlist->addMedia(QUrl("qrc:/sounds/bgsound.mp3"));
   playlist->setPlaybackMode(QMediaPlaylist::Loop);

   backgroundMusic = new QMediaPlayer();
   backgroundMusic->setPlaylist(playlist);
   backgroundMusic->setVolume(20);
   backgroundMusic->play();

}


//TOWER SLOTS

void Game::setTower1(){
    towerSelected = 0;
}

void Game::setTower2(){
    towerSelected = 1;
}
void Game::setTower3(){
    towerSelected = 2;
}
void Game::setTower4(){
    towerSelected = 3;
}




