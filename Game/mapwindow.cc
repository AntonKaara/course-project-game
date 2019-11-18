#include "core/resourcemaps.h"
#include "core/worldgenerator.h"

#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "mapitem.h"
#include "grasstile.h"
#include "foresttile.h"
#include "headquarters.h"
#include "outpost.h"
#include "farm.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "gamescene.h"

#include <memory>
#include <math.h>
#include <iostream>
#include <QDirIterator>
#include <QPixmap>
#include <string>

namespace Aeta {

MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    ui_(new Ui::MapWindow),
    scene_(new GameScene(this)) {

    ui_->setupUi(this);

    // Set scene

    GameScene* sgs_rawptr = scene_.get();
    ui_->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    scene_->installEventFilter(this);

    addPixmaps();

    // Add pictures

    QPixmap CoinPic(":/pictures/pictures/Coins.png");
    QPixmap FoodPic(":/pictures/pictures/Food.png");
    QPixmap WorkforcePic(":/pictures/pictures/Workforce.png");
    QPixmap HQPic(":/pictures/pictures/Headquarters.png");
    ui_->coinImg->setPixmap(CoinPic);
    ui_->foodImg->setPixmap(FoodPic);
    ui_->workforceImg->setPixmap(WorkforcePic);

    //ui_->buildList->item(0)->setIcon(pixmaps_.at("Farm"));
    //ui_->buildList->item(1)->setIcon(pixmaps_.at("Farm"));
    //ui_->buildList->item(2)->setIcon(pixmaps_.at("Farm"));
    //ui_->buildList->item(3)->setIcon(pixmaps_.at("Farm"));

    // Widget config

    ui_->tabWidget->setTabEnabled(0, false);
    ui_->tabWidget->setTabEnabled(1, false);
    ui_->tabWidget->setTabEnabled(2, false);
    ui_->endTurnButton->setStyleSheet("background-color:darkRed;" "color:white");

    // Create eventhandler & objectmanager objects

    auto gameEventHandler = std::make_shared<GameEventHandler>();
    auto objectManager = std::make_shared<ObjectManager>();
    gameEventHandler_ = gameEventHandler;
    objectManager_ = objectManager;

    /* Build map and setup the player objects and the starting buildings
     * for both
     */

    generateMap();
    drawMap();
    initializePlayer1();
    initializePlayer2();
    playerInTurn_ = players_.at(0);
    updateUI();

}

MapWindow::~MapWindow() {

    delete ui_;

}

void MapWindow::generateMap() {

    unsigned int seed = 123488; // Add random generation?

    Course::WorldGenerator& worldGen = worldGen.getInstance();

    // Add tile types
    worldGen.addConstructor<GrassTile>(80);
    worldGen.addConstructor<ForestTile>(20);

    worldGen.generateMap(static_cast<uint>(mapsizeX_), static_cast<uint>(mapsizeY_),
                         seed, objectManager_, gameEventHandler_);

}

void MapWindow::initializePlayer1() {

    // Create Player object

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    auto playerObject = std::make_shared<Player>(player1Name_, objects, 1);
    players_.push_back(playerObject);
    auto player = players_.back();
    qDebug() << "players.back" <<QString::fromStdString(players_.back()->getName());

    /* Create starting buildings and units for the player and add
     * them to the game
     */

    std::shared_ptr<Headquarters> headquarters = std::make_shared<
            Headquarters>(gameEventHandler_, objectManager_, player,
                          1, Course::ConstResourceMaps::HQ_BUILD_COST,
                          Course::ConstResourceMaps::HQ_PRODUCTION);

    std::shared_ptr<Farm> farm = std::make_shared<
            Farm>(gameEventHandler_, objectManager_, player,
                  1, Course::ConstResourceMaps::FARM_BUILD_COST,
                  Course::ConstResourceMaps::FARM_PRODUCTION);

    objectManager_->addBuilding(headquarters);
    player->addObject(headquarters);


    auto location = std::make_shared<Course::Coordinate>(2, 2);
    Course::Coordinate& locationRef = *location;
    std::shared_ptr<Course::TileBase> tileObject = objectManager_->getTile(locationRef);
    tileObject->setOwner(player);
    tileObject->addBuilding(headquarters);
    headquarters->onBuildAction();

    objectManager_->addBuilding(farm);
    player->addObject(farm);

    locationRef.set_x(1);
    locationRef.set_y(2);
    tileObject = objectManager_->getTile(locationRef);

    tileObject->setOwner(player);
    tileObject->addBuilding(farm);


    ui_->turnLabel->setText(QString::fromStdString(player1Name_) + "'s turn");
    ui_->graphicsView->centerOn(3, 3);

}

void MapWindow::initializePlayer2() {

    // Create Player object

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    auto playerObject = std::make_shared<Player>(player2Name_, objects, 2);
    players_.push_back(playerObject);
    auto player = players_.back();
    qDebug() << "players.back" <<QString::fromStdString(players_.back()->getName());

    /* Create starting buildings and units for the player and add
     * them to the game
     */

    std::shared_ptr<Headquarters> headquarters = std::make_shared<
            Headquarters>(gameEventHandler_, objectManager_, player,
                          1, Course::ConstResourceMaps::HQ_BUILD_COST,
                          Course::ConstResourceMaps::HQ_PRODUCTION);

    std::shared_ptr<Farm> farm = std::make_shared<
            Farm>(gameEventHandler_, objectManager_, player,
                  1, Course::ConstResourceMaps::FARM_BUILD_COST,
                  Course::ConstResourceMaps::FARM_PRODUCTION);

    objectManager_->addBuilding(headquarters);
    player->addObject(headquarters);


    auto location = std::make_shared<Course::Coordinate>(mapsizeX_ - 3, mapsizeY_ - 3);
    Course::Coordinate& locationRef = *location;
    std::shared_ptr<Course::TileBase> tileObject = objectManager_->getTile(locationRef);
    tileObject->setOwner(player);
    tileObject->addBuilding(headquarters);
    headquarters->onBuildAction();

    objectManager_->addBuilding(farm);
    player->addObject(farm);

    locationRef.set_x(mapsizeX_ - 4);
    locationRef.set_y(mapsizeY_ - 3);
    tileObject = objectManager_->getTile(locationRef);

    tileObject->setOwner(player);
    tileObject->addBuilding(farm);


    ui_->turnLabel->setText(QString::fromStdString(player2Name_) + "'s turn");
    ui_->graphicsView->centerOn(3, 3);

}

void MapWindow::buildOnTile() {
    QString buildingToBuild = ui_->buildList->currentItem()->text();
    std::shared_ptr<Course::TileBase> tile = objectManager_->getTile(selectedTileID_);

    if (tile->getOwner() != playerInTurn_) {
        qDebug() << "Wrong owner";
        return;
    }

    if (buildingToBuild == "Farm") {

        std::shared_ptr<Farm> farm = std::make_shared<
                Farm>(gameEventHandler_, objectManager_, playerInTurn_,
                      1, Course::ConstResourceMaps::FARM_BUILD_COST,
                      Course::ConstResourceMaps::FARM_PRODUCTION);

        objectManager_->addBuilding(farm);
        playerInTurn_->addObject(farm);
        tile->setOwner(playerInTurn_);
        tile->addBuilding(farm);
        farm->onBuildAction();

    } else if (buildingToBuild == "Outpost") {

        std::shared_ptr<Outpost> outpost = std::make_shared<Outpost>
                (gameEventHandler_, objectManager_, playerInTurn_,
                      1, Course::ConstResourceMaps::FARM_BUILD_COST,
                      Course::ConstResourceMaps::FARM_PRODUCTION);

        objectManager_->addBuilding(outpost);
        playerInTurn_->addObject(outpost);
        tile->setOwner(playerInTurn_);
        tile->addBuilding(outpost);
        outpost->onBuildAction();

    }

    updateUI();
    scene_->update();

}

void MapWindow::endTurn() {

    qDebug() << "End turn pressed";

    if (turn_ % 2 == 0) {
        playerInTurn_ = players_.at(1);
    } else {
        playerInTurn_ = players_.at(0);
    }

    turn_ += 1;

    ui_->turnCountLabel->setText("Turn: " + QString::fromStdString(std::to_string(turn_)));

    QString playerName = QString::fromStdString(playerInTurn_->getName());
    ui_->turnLabel->setText(playerName + "'s turn");

    // Center map on player HQ

    auto mapFocusLocation = std::make_shared<Course::Coordinate>(20, 20);
    for (auto obj : playerInTurn_->getObjects()) {
        if (obj->getType() == "Headquarters") {
            mapFocusLocation = obj->getCoordinatePtr();
        }
    }
    qDebug() << "Camera location to" << mapFocusLocation->x() << mapFocusLocation->y();
    double xCoordinate = mapFocusLocation->x();
    double yCoordinate = mapFocusLocation->y();
    ui_->graphicsView->centerOn(xCoordinate, yCoordinate);

    scene_->update();

    qDebug() << "player in turn " << QString::fromStdString(playerInTurn_->getName());

}

void MapWindow::drawMap() {

    setSize(mapsizeX_, mapsizeY_);
    setScale(mapScale_);

    // Coordinate-object
    auto location = std::make_shared<Course::Coordinate>(0, 0);
    Course::Coordinate& locationRef = *location;

    // Draw each tile and set coordinates for the tiles

    //int x = 0;
    //int y = 0;

    while (locationRef.x() < mapsizeX_) {

        while (locationRef.y() < mapsizeY_){
            auto tile = objectManager_->getTile(locationRef);
            drawTile(tile);
            //y++;
            locationRef.set_y(locationRef.y() + 1);
        }

        //x++;
        locationRef.set_x(locationRef.x() + 1);
        //y = 0;
        locationRef.set_y(0);
    }

}

void MapWindow::setSize(int width, int height) {

    scene_->setSize(width, height);

}

void MapWindow::setScale(int scale) {

    scene_->setScale(scale);

}

void MapWindow::resize() {

    scene_->resize();

}

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj) {

    scene_->updateItem(obj);

}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj) {

    scene_->removeItem(obj);

}

void MapWindow::drawTile( std::shared_ptr<Course::TileBase> obj) {

    scene_->drawTile(obj);

}

void MapWindow::on_zoomInButton_clicked() {

    if (zoomLevel_ < 2) {
        ui_->graphicsView->scale(2, 2);
        zoomLevel_ += 1;

        if (zoomLevel_ == 2) {
            ui_->zoomInButton->setEnabled(false);
        }

        if (zoomLevel_ > -2) {
            ui_->zoomOutButton->setEnabled(true);
        }
    }

}

void MapWindow::on_zoomOutButton_clicked() {

    if (zoomLevel_ > -2) {
        ui_->graphicsView->scale(0.5, 0.5);
        zoomLevel_ -= 1;

        if (zoomLevel_ == -2) {
            ui_->zoomOutButton->setEnabled(false);
        }

        if (zoomLevel_ < 2) {
            ui_->zoomInButton->setEnabled(true);
        }

    }

}

void Aeta::MapWindow::on_endTurnButton_clicked() {

    endTurn();

}

void Aeta::MapWindow::on_buildPanelButton_clicked() {

    ui_->tabWidget->setTabEnabled(1, true);
    ui_->tabWidget->setCurrentIndex(1);

}

void Aeta::MapWindow::on_confirmBuildButton_clicked() {

    ui_->tabWidget->setCurrentIndex(0);
    ui_->tabWidget->setTabEnabled(1, false);

    buildOnTile();

}

void Aeta::MapWindow::on_buildList_itemDoubleClicked(QListWidgetItem *item) {

   on_confirmBuildButton_clicked();

}

void MapWindow::updateUI() {

    // Close build-tab and open tile-tab
    ui_->tabWidget->setTabEnabled(0, true);
    ui_->tabWidget->setCurrentIndex(0);
    ui_->tabWidget->setTabEnabled(1, false);

    // Get gameobjects on tile
    std::shared_ptr<Course::TileBase> tile = objectManager_->getTile(selectedTileID_);
    std::shared_ptr<Course::BuildingBase> building = nullptr;
    std::shared_ptr<Course::WorkerBase> unit = nullptr;

    // Get names and descriptions
    QString tileType = QString::fromStdString(tile->getType());
    QString tileDesc = QString::fromStdString(tile->getDescription("basic"));
    QString buildingType = "No buildings";
    QString buildingDesc = "Null";
    QString unitType = "Null_unit";
    QPixmap pic = pixmaps_.at(tile->getType());

    // Update tile info label
    if (tile->getBuildings().size() > 0) {
        building = tile->getBuildings().at(0);
        buildingType = QString::fromStdString(building->getType());
        buildingDesc = QString::fromStdString(building->getDescription("basic"));

        pic = pixmaps_.at(building->getType());
        ui_->tileHeaderLabel->setText(buildingType);
        ui_->tileDescriptionLabel->setText(buildingDesc);
        ui_->buildPanelButton->setEnabled(false);
    } else {
        ui_->tileHeaderLabel->setText(tileType);
        ui_->tileDescriptionLabel->setText(tileDesc);
        ui_->buildPanelButton->setEnabled(true);
    }

    // Update owner label
    if (tile->getOwner() != nullptr) {
        QString playerName = QString::fromStdString(tile->getOwner()->getName());
        ui_->tileOwnerLabel->setText("Owned by " + playerName);
    } else {
        ui_->tileOwnerLabel->setText("Owned by nobody");
    }

    // Update unit tab
    if (tile->getWorkers().size() > 0) {
        unit = tile->getWorkers().at(0);
        unitType = QString::fromStdString(unit->getType());
        ui_->tabWidget->setTabEnabled(2, true);
    } else {
        ui_->tabWidget->setTabEnabled(2, false);
    }

    ui_->tileImgLabel->setPixmap(pic);
    ui_->unitTypeLabel->setText("Type: " + unitType);

    // Turn label updates
    ui_->turnCountLabel->setText("Turn: " + QString::fromStdString(std::to_string(turn_)));
    QString playerName = QString::fromStdString(playerInTurn_->getName());
    ui_->turnLabel->setText(playerName + "'s turn");
}

bool MapWindow::eventFilter(QObject *object, QEvent *event) {

    if (object == &*scene_ && event->type() == QEvent::GraphicsSceneMousePress) {
            qDebug() << "Jee se toimii, nyt kutsu";
            uint tileID = scene_->tileClicked(event);
            qDebug() << "Got tileID: " << tileID;
            selectedTileID_ = tileID;
            updateUI();
            return true;
    }

    return false;

}

void MapWindow::resizeEvent(QResizeEvent *event) {
    qDebug() << "resize event, tabwidget height: " << ui_->tabWidget->height();
    ui_->buildList->resize(ui_->tabWidget->width(), ui_->tabWidget->height() - 88);
}

void MapWindow::addPixmaps() {

    std::vector<std::string> types = {"Archer", "Farm", "Forest", "Grass", "Headquarters",
                                      "Infantry", "outpostPlayer1", "outpostPlayer2"};

    for (auto mapItemType : types) {
        QString filePath = QString::fromStdString(":/pictures/pictures/"
                                                  + mapItemType + ".png");
        QPixmap image(filePath);
        pixmaps_.insert({mapItemType, image});
    }

}

} // namespace Aeta


