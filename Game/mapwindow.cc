#include "core/resourcemaps.h"
#include "core/worldgenerator.h"

#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "mapitem.h"
#include "grasstile.h"
#include "foresttile.h"
#include "swamp.h"
#include "lake.h"
#include "mountain.h"
#include "outpost.h"
#include "farm.h"
#include "lumbermill.h"
#include "mine.h"
#include "infantry.h"
#include "archery.h"
#include "cavalry.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "gamescene.h"

#include <memory>
#include <math.h>
#include <iostream>
#include <QDirIterator>
#include <QPixmap>
#include <string>
#include <QMouseEvent>

namespace Aeta {

MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    ui_(new Ui::MapWindow),
    scene_(new GameScene(this)) {

    ui_->setupUi(this);

    /* Create menu window and connect all its properties to
     * mapwindow's (this) slots
     */

    mainMenu_ = std::make_shared<MainMenu>(this);

    connect(&*mainMenu_, &MainMenu::playerNameChanged,
            this, &MapWindow::setPlayerName);
    connect(&*mainMenu_, &MainMenu::mapSizeChanged,
            this, &MapWindow::setMapSize);


    // show menu dialog and if the quit button is pressed end the program

    int result = mainMenu_->exec();
    if (result == MainMenu::Rejected) {
        exit(EXIT_SUCCESS);
    }

    // Set scene

    GameScene* sgs_rawptr = scene_.get();
    ui_->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    scene_->installEventFilter(this);

    addPixmaps();

    // Add pictures

    ui_->coinImg->setPixmap(pixmaps_.at("Coins"));
    ui_->foodImg->setPixmap(pixmaps_.at("Food"));
    ui_->workforceImg->setPixmap(pixmaps_.at("Workforce"));
    ui_->woodImg->setPixmap(pixmaps_.at("Wood"));

    // Widget config

    ui_->tabWidget->setTabEnabled(0, false);
    ui_->tabWidget->setTabEnabled(1, false);
    ui_->tabWidget->setTabEnabled(2, false);
    ui_->buildPanelButton->setVisible(false);
    ui_->recruitButton->setVisible(false);
    ui_->endTurnButton->setStyleSheet("background-color:darkRed;" "color:white");
    ui_->confirmBuildButton->setStyleSheet("background-color:darkGreen;" "color:white");
    ui_->confirmRecruitButton->setStyleSheet("background-color:darkGreen;" "color:white");
    ui_->moveButton->setStyleSheet("background-color:#165581;" "color:white");

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
    centerViewtoHQ();

}

MapWindow::~MapWindow() {

    delete ui_;

}

void MapWindow::generateMap() {

    unsigned int seed = 123488; // TODO: Add random generation

    Course::WorldGenerator& worldGen = worldGen.getInstance();

    // Add tile types
    worldGen.addConstructor<GrassTile>(200);
    worldGen.addConstructor<ForestTile>(75);
    worldGen.addConstructor<Swamp>(2);
    worldGen.addConstructor<Lake>(6);
    worldGen.addConstructor<Mountain>(4);

    worldGen.generateMap(static_cast<uint>(mapsizeX_), static_cast<uint>(mapsizeY_),
                         seed, objectManager_, gameEventHandler_);

}

void MapWindow::initializePlayer1() {

    // Create Player object

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    auto playerObject = std::make_shared<Player>("1", objects);
    players_.push_back(playerObject);
    auto player = players_.back();
    qDebug() << "players.back" <<QString::fromStdString(players_.back()->getName());

    /* Create starting buildings and units for the player and add
     * them to the game
     */

    // TODO: Change tile to grass before building

    // Create objects

    std::shared_ptr<Headquarters> headquarters = std::make_shared<
            Headquarters>(gameEventHandler_, objectManager_, player,
                          1, Course::ConstResourceMaps::HQ_BUILD_COST,
                          Course::ConstResourceMaps::HQ_PRODUCTION);

    std::shared_ptr<Farm> farm = std::make_shared<
            Farm>(gameEventHandler_, objectManager_, player,
                  1, Course::ConstResourceMaps::FARM_BUILD_COST,
                  Course::ConstResourceMaps::FARM_PRODUCTION);


    std::shared_ptr<Infantry> infantry = std::make_shared<
            Infantry>(gameEventHandler_, objectManager_, player,
                  1, Course::ConstResourceMaps::BW_RECRUITMENT_COST,
                  Course::ConstResourceMaps::BW_WORKER_EFFICIENCY);


    // Add HQ
    objectManager_->addBuilding(headquarters);
    player->addObject(headquarters);
    auto location = std::make_shared<Course::Coordinate>(2, 2);
    Course::Coordinate& locationRef = *location;
    std::shared_ptr<Course::TileBase> tileObject = objectManager_->getTile(locationRef);

    tileObject->setOwner(player);
    tileObject->addBuilding(headquarters);
    headquarters->onBuildAction();

    player1HQ_ = headquarters;

    // Add Farm
    objectManager_->addBuilding(farm);
    player->addObject(farm);
    locationRef.set_x(3);
    locationRef.set_y(2);
    tileObject = objectManager_->getTile(locationRef);

    tileObject->setOwner(player);
    tileObject->addBuilding(farm);
    //farm->onBuildAction();

    // Add Infantry
    objectManager_->addUnit(infantry);
    player->addObject(infantry);
    locationRef.set_x(2);
    locationRef.set_y(3);
    tileObject = objectManager_->getTile(locationRef);

    tileObject->setOwner(player);
    tileObject->addWorker(infantry);

}

void MapWindow::initializePlayer2() {

    // Create Player object

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    auto playerObject = std::make_shared<Player>("2", objects);
    players_.push_back(playerObject);
    auto player = players_.back();
    qDebug() << "players.back" <<QString::fromStdString(players_.back()->getName());

    /* Create starting buildings and units for the player and add
     * them to the game
     */

    // Create objects

    std::shared_ptr<Headquarters> headquarters = std::make_shared<
            Headquarters>(gameEventHandler_, objectManager_, player,
                          1, Course::ConstResourceMaps::HQ_BUILD_COST,
                          Course::ConstResourceMaps::HQ_PRODUCTION);

    std::shared_ptr<Farm> farm = std::make_shared<
            Farm>(gameEventHandler_, objectManager_, player,
                  1, Course::ConstResourceMaps::FARM_BUILD_COST,
                  Course::ConstResourceMaps::FARM_PRODUCTION);

    std::shared_ptr<Infantry> infantry = std::make_shared<
            Infantry>(gameEventHandler_, objectManager_, player,
                  1, Course::ConstResourceMaps::BW_RECRUITMENT_COST,
                  Course::ConstResourceMaps::BW_WORKER_EFFICIENCY);

    // Add HQ
    objectManager_->addBuilding(headquarters);
    player->addObject(headquarters);
    auto location = std::make_shared<Course::Coordinate>(mapsizeX_ - 3, mapsizeY_ - 3);
    Course::Coordinate& locationRef = *location;
    std::shared_ptr<Course::TileBase> tileObject = objectManager_->getTile(locationRef);

    tileObject->setOwner(player);
    tileObject->addBuilding(headquarters);
    headquarters->onBuildAction();

    player2HQ_ = headquarters;

    // Add Farm
    objectManager_->addBuilding(farm);
    player->addObject(farm);
    locationRef.set_x(mapsizeX_ - 4);
    locationRef.set_y(mapsizeY_ - 3);
    tileObject = objectManager_->getTile(locationRef);

    tileObject->setOwner(player);
    tileObject->addBuilding(farm);
    //farm->onBuildAction();

    // Add Infantry
    objectManager_->addUnit(infantry);
    player->addObject(infantry);
    locationRef.set_x(mapsizeX_ - 3);
    locationRef.set_y(mapsizeY_ - 4);
    tileObject = objectManager_->getTile(locationRef);

    tileObject->setOwner(player);
    tileObject->addWorker(infantry);

}

void MapWindow::buildOnTile() {

    QString buildingToBuild = ui_->buildList->currentItem()->text();
    std::shared_ptr<Course::TileBase> tile = selectedTile_;

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

    } else if (buildingToBuild == "Mine") {

        std::shared_ptr<Mine> mine = std::make_shared<Mine>
                (gameEventHandler_, objectManager_, playerInTurn_,
                      1, Course::ConstResourceMaps::FARM_BUILD_COST,
                      Course::ConstResourceMaps::FARM_PRODUCTION);

        objectManager_->addBuilding(mine);
        playerInTurn_->addObject(mine);
        tile->setOwner(playerInTurn_);
        tile->addBuilding(mine);
        mine->onBuildAction();

    } else if (buildingToBuild == "Lumber Mill") {

        std::shared_ptr<Lumbermill> lumbermill = std::make_shared<Lumbermill>
                (gameEventHandler_, objectManager_, playerInTurn_,
                      1, Course::ConstResourceMaps::FARM_BUILD_COST,
                      Course::ConstResourceMaps::FARM_PRODUCTION);

        objectManager_->addBuilding(lumbermill);
        playerInTurn_->addObject(lumbermill);
        tile->setOwner(playerInTurn_);
        tile->addBuilding(lumbermill);
        lumbermill->onBuildAction();

    }

    updateUI();
    scene_->update();

}

void MapWindow::endTurn() {

    turn_ += 1;
    if (playerInTurn_->getName() == "2") {
        turnCount_ += 1;
    }

    // Add movement points to current player

    for (auto unit : objectManager_->getAllUnits()) {
        if (unit->getOwner() == playerInTurn_) {
            unit->resetMovement();
        }
    }

    // Change player in turn

    if (turn_ % 2 == 0) {
        playerInTurn_ = players_.at(1);
    } else {
        playerInTurn_ = players_.at(0);
    }

    moveMode_ = false;
    centerViewtoHQ();
    scene_->update();
    updateUI();

}

void MapWindow::centerViewtoHQ() {

    auto mapFocusLocation = std::make_shared<Course::Coordinate>(10, 10);
    for (auto obj : playerInTurn_->getObjects()) {
        if (obj->getType() == "Headquarters") {
            mapFocusLocation = obj->getCoordinatePtr();
            qDebug() << "ID" << QString::fromStdString(std::to_string(obj->ID));
        }
    }

    qDebug() << "Camera location to" << mapFocusLocation->x() << mapFocusLocation->y();
    double xCoordinate = mapFocusLocation->x();
    double yCoordinate = mapFocusLocation->y();
    ui_->graphicsView->centerOn(QPointF(xCoordinate * 60, yCoordinate * 60));

    Course::Coordinate& locationRef = *mapFocusLocation;
    selectedTile_ = objectManager_->getTile(locationRef);
}

void MapWindow::drawMap() {

    setSize(mapsizeX_, mapsizeY_);
    setScale(mapScale_);

    // Coordinate-object
    auto location = std::make_shared<Course::Coordinate>(0, 0);
    Course::Coordinate& locationRef = *location;

    // Draw each tile and set coordinates for the tiles

    while (locationRef.x() < mapsizeX_) {

        while (locationRef.y() < mapsizeY_){
            auto tile = objectManager_->getTile(locationRef);
            drawTile(tile);
            locationRef.set_y(locationRef.y() + 1);
        }
        locationRef.set_x(locationRef.x() + 1);
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

void MapWindow::on_endTurnButton_clicked() {

    endTurn();

}

void MapWindow::on_buildPanelButton_clicked() {

    ui_->tabWidget->setTabEnabled(1, true);
    ui_->tabWidget->setCurrentIndex(1);

}

void MapWindow::on_confirmBuildButton_clicked() {

    ui_->tabWidget->setCurrentIndex(0);
    ui_->tabWidget->setTabEnabled(1, false);

    buildOnTile();

}

void MapWindow::on_buildList_itemDoubleClicked(QListWidgetItem *item) {

   on_confirmBuildButton_clicked();

}

void MapWindow::on_unitTextBox_editingFinished() {
    selectedUnit_->setName(ui_->unitTextBox->text().toStdString());
}

void Aeta::MapWindow::on_moveButton_clicked() {

    if (moveMode_) {
        moveMode_ = false;
    } else {
        moveMode_ = true;
    }

    updateUI();

}

void Aeta::MapWindow::on_recruitButton_clicked() {

    ui_->tabWidget->setTabEnabled(3, true);
    ui_->tabWidget->setCurrentIndex(3);

}

void Aeta::MapWindow::on_confirmRecruitButton_clicked() {

    ui_->tabWidget->setCurrentIndex(0);
    ui_->tabWidget->setTabEnabled(3, false);

    recruitUnit();

}

void Aeta::MapWindow::on_recruitList_doubleClicked(const QModelIndex &index) {

    on_confirmRecruitButton_clicked();

}

void MapWindow::setPlayerName(const QString &name, const int &playerNumber) {

    if (playerNumber == 1) {
        player1UiName_ = name;
    } else {
        player2UiName_ = name;
    }

}

void MapWindow::setMapSize(const int &sizeX, const int &sizeY) {
    mapsizeX_ = sizeX;
    mapsizeY_ = sizeY;
}

void MapWindow::updateUI() {

    // Close build-tab and open tile-tab
    ui_->tabWidget->setTabEnabled(0, true);
    ui_->tabWidget->setCurrentIndex(0);
    ui_->tabWidget->setTabEnabled(1, false);
    ui_->tabWidget->setTabEnabled(3, false);
    ui_->recruitButton->setVisible(false);
    ui_->buildingHPLabel->setVisible(false);
    ui_->buildingHPBar->setVisible(false);

    if (selectedTile_ != nullptr) {

        // Get gameobjects on tile
        std::shared_ptr<Course::TileBase> tile = selectedTile_;
        std::shared_ptr<Course::BuildingBase> building = nullptr;
        std::shared_ptr<UnitBase> unit = nullptr;

        // Get names and descriptions
        QString tileType = QString::fromStdString(tile->getType());
        QString tileDesc = QString::fromStdString(tile->getDescription("basic"));
        QString buildingType = "No buildings";
        QString buildingDesc = "Null";
        QString unitType = "Null_unit";
        QPixmap pic = pixmaps_.at(tile->getType());
        QPixmap unitPic = pixmaps_.at(tile->getType());

        if (tile->getBuildings().size() > 0) {
            building = tile->getBuildings().at(0);
            buildingType = QString::fromStdString(building->getType());
            buildingDesc = QString::fromStdString(building->getDescription("basic"));

            // Update tile info label
            pic = pixmaps_.at(building->getType());
            ui_->tileHeaderLabel->setText(buildingType);
            ui_->tileDescriptionLabel->setText(buildingDesc);
            ui_->buildPanelButton->setEnabled(false);
            ui_->buildPanelButton->setText("Demolish");
            ui_->buildPanelButton->setToolTip("Demolish the building on this tile");
            ui_->buildPanelButton->setStyleSheet("background-color:darkRed;" "color:white");

            if (buildingType == "Headquarters") {

                if (building->getOwner() == playerInTurn_) {
                    ui_->recruitButton->setVisible(true);
                }

                // Set HQ HitPoints bar value
                if (building->getOwner()->getName() == "1") {
                    ui_->buildingHPBar->setValue(player1HQ_->getHitPoints());
                } else if (building->getOwner()->getName() == "2"){
                    ui_->buildingHPBar->setValue(player2HQ_->getHitPoints());
                }

                // Only show hitpoints if HQ damaged
                if (player1HQ_->getHitPoints() < 100 && building->getOwner()->getName() == "1") {
                    ui_->buildingHPLabel->setVisible(true);
                    ui_->buildingHPBar->setVisible(true);
                } else if (player2HQ_->getHitPoints() < 100 && building->getOwner()->getName() == "2") {
                    ui_->buildingHPLabel->setVisible(true);
                    ui_->buildingHPBar->setVisible(true);
                }

                ui_->buildPanelButton->setText("Disabled");
                ui_->buildPanelButton->setToolTip("You can not move the headquarters");
                ui_->buildPanelButton->setStyleSheet("background-color:gray;" "color:white");
            }

        } else {
            ui_->tileHeaderLabel->setText(tileType);
            ui_->tileDescriptionLabel->setText(tileDesc);
            ui_->buildPanelButton->setEnabled(true);
            ui_->buildPanelButton->setText("Build");
            ui_->buildPanelButton->setToolTip("Build a building on the this tile");
            ui_->buildPanelButton->setStyleSheet("background-color:darkGreen;" "color:white");
        }

        if (tile->getOwner() != nullptr) {

            // Update owner label
            QString playerName = QString::fromStdString(tile->getOwner()->getName());
            if (playerName == "1") {
                ui_->tileOwnerLabel->setText("Owned by " + player1UiName_);
            } else {
                ui_->tileOwnerLabel->setText("Owned by " + player2UiName_);
            }

            // Disable tile buttons if not own tile
            if (tile->getOwner() == playerInTurn_) {
                ui_->buildPanelButton->setVisible(true);
            } else {
                ui_->buildPanelButton->setVisible(false);
                ui_->tabWidget->setTabEnabled(1, false);
                ui_->recruitButton->setVisible(false);
                ui_->tabWidget->setTabEnabled(3, false);
            }

        } else {
            ui_->tileOwnerLabel->setText("Owned by nobody");
            ui_->buildPanelButton->setVisible(false);
            ui_->recruitButton->setVisible(false);
        }

        // Update unit tab
        if (tile->getWorkers().size() > 0) {
            auto tileLocation = tile->getCoordinate();
            unit = objectManager_->getUnit(tileLocation);
            unitType = QString::fromStdString(unit->getType());

            ui_->unitTypeLabel->setText("Type: " + unitType);
            ui_->unitTextBox->setText(QString::fromStdString(unit->getName()));
            ui_->healthBar->setValue(unit->getHealth());
            ui_->movementPointNumber->setText(QString::fromStdString(std::to_string(unit->getMovement())));

            if (playerInTurn_ != unit->getOwner()) {
                ui_->moveButton->setVisible(false);
            } else {
                ui_->moveButton->setVisible(true);
            }

            // Set UI picture

            unitPic = pixmaps_.at(unit->getType());

            ui_->unitImgLabel->setPixmap(unitPic);

            ui_->tabWidget->setTabEnabled(2, true);
            ui_->tabWidget->setCurrentIndex(2);
        } else {
            ui_->tabWidget->setTabEnabled(2, false);
            ui_->tabWidget->setCurrentIndex(0);
        }

        ui_->tileImgLabel->setPixmap(pic);

    }

    // Update move button
    if (moveMode_) {
        ui_->moveButton->setStyleSheet("background-color:yellow;" "color:black");
        ui_->moveButton->setText("Cancel move");
    } else {
        ui_->moveButton->setStyleSheet("background-color:#165581;" "color:white");
        ui_->moveButton->setText("Move / Attack");
    }

    // Turn label updates

    ui_->turnCountLabel->setText("Turn: " + QString::fromStdString(std::to_string(turnCount_)));
    QString playerName = QString::fromStdString(playerInTurn_->getName());

    if (playerName == "1") {
        ui_->turnLabel->setText(player1UiName_ + "'s turn");
    } else {
        ui_->turnLabel->setText(player2UiName_ + "'s turn");
    }

}

void MapWindow::cutForest(const std::shared_ptr<Course::TileBase> &tile) {

    Course::Coordinate location = tile->getCoordinate();

    objectManager_->removeTile(tile);

    // TODO: Add resources to player

}

bool MapWindow::attackHQ(const std::shared_ptr<Course::TileBase> &tile, const std::shared_ptr<UnitBase> &attacker) {

    std::shared_ptr<Headquarters> HQ = std::dynamic_pointer_cast<Headquarters>(tile->getBuildings().at(0));
    HQ->changeHitPoints((attacker->getDamage()) * (-1));

    if (HQ->getHitPoints() <= 0) {
        return true; // Tell caller that HQ has been destroyed
    } else {
        return false;
    }

}

bool MapWindow::moveUnit(const std::shared_ptr<Course::TileBase> &tile) {
    int movementPoints = selectedUnit_->getMovement();

    if (movementPoints >= 1) { // Enough movement points

        for (auto coordinate : selectedTile_->getCoordinate().neighbours()) {

            if (tile->getCoordinate() == coordinate) { // Clicked tile is one of the neighbors

                if (tile->getType() == "Grass" || tile->getType() == "Forest") {

                    if (tile->getWorkerCount() < 1) { // Tile is free of units

                        if (tile->getOwner() != selectedUnit_->getOwner()) { // It's enemy tile

                            // Tile ownership to current player
                            if (tile->getOwner() != playerInTurn_ && tile->getOwner() != nullptr) {
                                tile->setOwner(selectedUnit_->getOwner());
                                tilesToGiveBack_.push_back(tile);
                            }

                            // Destroy possible enemy building
                            if (tile->getBuildingCount() > 1) {
                                auto building = tile->getBuildings().at(0);

                                // Attack HQ
                                if (building->getType() == "Headquarters") {
                                    bool HQDestroyed = attackHQ(tile, selectedUnit_);
                                    qDebug() << "HQ took damage";

                                    if (HQDestroyed) {
                                        tile->removeBuilding(building);
                                        objectManager_->removeBuilding(building);
                                        qDebug() << "HQ DESTROYED";
                                    }

                                } else {

                                }
                            }
                        }

                        selectedUnit_->setCoordinate(coordinate);
                        selectedTile_->removeWorker(selectedUnit_);
                        tile->addWorker(selectedUnit_);
                        qDebug() << "Moved to: " << coordinate.x() << coordinate.y();
                        selectedUnit_->changeMovement(-1);

                    } else {
                        qDebug() << "Tile already occupied";

                        // Attack enemy unit
                        std::shared_ptr<UnitBase> otherUnit = objectManager_->getUnit(tile->getCoordinate());
                        if (otherUnit->getOwner() != selectedUnit_->getOwner()) {
                            bool enemyDied = selectedUnit_->attackUnit(otherUnit);
                            qDebug() << "Enemy unit took damage";

                            selectedUnit_->setMovement(0);

                            if (enemyDied) {
                                tile->removeWorker(otherUnit);
                                objectManager_->removeUnit(otherUnit);
                                qDebug() << "Enemy unit died";
                            }
                        }

                    }

                } else if (tile->getType() == "Swamp") { // If not grass or forest


                    selectedUnit_->setCoordinate(coordinate);
                    selectedTile_->removeWorker(selectedUnit_);
                    tile->addWorker(selectedUnit_);
                    qDebug() << "Moved to: " << coordinate.x() << coordinate.y();
                    selectedUnit_->changeMovement(-2);

                } else {
                    return false;
                }

                // Give back tiles
                for (auto tile : tilesToGiveBack_) {
                    if (tile->getWorkerCount() < 1) {
                        for (auto player : players_) {
                            if (player != playerInTurn_) {
                                tile->setOwner(player);
                            }
                        }
                    }
                }

                moveMode_ = false;
                //ui_->moveButton->setText("Move");
                selectedTile_ = tile;
                //selectedUnit_ = objectManager_->getUnit(coordinate);
                scene_->update();
                updateUI();
                return true;
            }
        }
    } else {
        qDebug() << "Not enough movement points";
    }
    return false;
}

void MapWindow::recruitUnit() {

    QString unitToRecruit = ui_->recruitList->currentItem()->text();
    std::shared_ptr<Course::TileBase> tile = nullptr;
    Course::Coordinate location = {3, 3};

    if (selectedTile_ != nullptr) {
        location = selectedTile_->getCoordinate().neighbours().at(5); // NEEDS WORK
    }

    tile = objectManager_->getTile(location);


    if (unitToRecruit == "Infantry") {

        std::shared_ptr<Infantry> infantry = std::make_shared<
                Infantry>(gameEventHandler_, objectManager_, playerInTurn_,
                      1, Course::ConstResourceMaps::BW_RECRUITMENT_COST,
                      Course::ConstResourceMaps::BW_WORKER_EFFICIENCY);

        objectManager_->addUnit(infantry);
        playerInTurn_->addObject(infantry);
        infantry->setOwner(playerInTurn_);
        tile->addWorker(infantry);
        //infantry->onBuildAction();

    } else if (unitToRecruit == "Archery") {

        std::shared_ptr<Archery> archery = std::make_shared<
                Archery>(gameEventHandler_, objectManager_, playerInTurn_,
                      1, Course::ConstResourceMaps::BW_RECRUITMENT_COST,
                      Course::ConstResourceMaps::BW_WORKER_EFFICIENCY);

        objectManager_->addUnit(archery);
        playerInTurn_->addObject(archery);
        archery->setOwner(playerInTurn_);
        tile->addWorker(archery);
        //archery->onBuildAction();

    } else if (unitToRecruit == "Cavalry") {

        std::shared_ptr<Cavalry> cavalry = std::make_shared<
                Cavalry>(gameEventHandler_, objectManager_, playerInTurn_,
                      1, Course::ConstResourceMaps::BW_RECRUITMENT_COST,
                      Course::ConstResourceMaps::BW_WORKER_EFFICIENCY);

        objectManager_->addUnit(cavalry);
        playerInTurn_->addObject(cavalry);
        cavalry->setOwner(playerInTurn_);
        tile->addWorker(cavalry);
        //cavalry->onBuildAction();

    }

    updateUI();
    scene_->update();

}

bool MapWindow::eventFilter(QObject *object, QEvent *event) {

    if (object == &*scene_ && event->type() == QEvent::GraphicsSceneMousePress) {

        if (moveMode_) {

            uint tileID = scene_->tileClicked(event, false);
            qDebug() << "Got tileID for moving: " << tileID;
            std::shared_ptr<Course::TileBase> moveToTile = objectManager_->getTile(tileID);

            if (moveUnit(moveToTile)) {
                scene_->tileClicked(event, true);
            }

        } else {

            uint tileID = scene_->tileClicked(event, true);
            qDebug() << "Got tileID: " << tileID;
            selectedTile_ = objectManager_->getTile(tileID);
            qDebug() << "selected tile ID: " << selectedTile_->ID;
            selectedUnit_ = objectManager_->getUnit(selectedTile_->getCoordinate());
            updateUI();
            return true;
        }

    }

    return false;

}

void MapWindow::resizeEvent(QResizeEvent *event) {
    qDebug() << "resize event, tabwidget height: " << ui_->tabWidget->height();
    ui_->buildList->resize(ui_->tabWidget->width(), ui_->tabWidget->height() - 88);
}

void MapWindow::addPixmaps() {

    std::vector<std::string> types = {"Archery",
                                      "Archery1Free", "Archery1Owned",
                                      "Archery2Free", "Archery2Owned",
                                      "Cavalry", "Cavalry1Free",
                                      "Cavalry1Owned", "Cavalry2Free",
                                      "Cavalry2Owned",
                                      "Coins", "Farm", "Farm1", "Farm2",
                                      "Food", "Forest", "Forest1",
                                      "Forest2", "Grass", "Grass1",
                                      "Grass2", "Headquarters",
                                      "Headquarters1", "Headquarters2",
                                      "Infantry",
                                      "Infantry1Free", "Infantry1Owned",
                                      "Infantry2Free", "Infantry2Owned",
                                      "Lake", "Lake1", "Lake2",
                                      "Lumbermill", "Lumbermill1",
                                      "Lumbermill2", "Mine", "Mine1",
                                      "Mine2", "Mountain", "Mountain1",
                                      "Mountain2",
                                      "Ore", "Outpost", "Outpost1",
                                      "Outpost2", "Swamp", "Swamp1",
                                      "Swamp2", "Wood", "Workforce"};

    for (auto mapItemType : types) {
        QString filePath = QString::fromStdString(":/pictures/pictures/"
                                                  + mapItemType + ".png");
        QPixmap image(filePath);
        pixmaps_.insert({mapItemType, image});
    }

}

} // namespace Aeta
