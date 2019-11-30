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
#include "resources.hh"

#include <memory>
#include <math.h>
#include <iostream>
#include <QDirIterator>
#include <QPixmap>
#include <string>
#include <QMouseEvent>
#include <QMessageBox>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>

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
    welcomeDialog_ = std::make_shared<Welcome>(this);
    winDialog_ = std::make_shared<WinDialog>(this);

    // Connect mainmenu signals to values here

    connect(&*mainMenu_, &MainMenu::playerNameChanged,
            this, &MapWindow::setPlayerName);
    connect(&*mainMenu_, &MainMenu::mapSizeChanged,
            this, &MapWindow::setMapSize);

    // Send highscores to victory dialog

    connect(this, &MapWindow::highScore,
            &*winDialog_, &WinDialog::setHighScore);

    // Show menu dialog and if the quit button is pressed end the program

    int result = mainMenu_->exec();
    if (result == MainMenu::Rejected) {
        exit(EXIT_SUCCESS);
    }

    // Set scene

    GameScene* sgs_rawptr = scene_.get();
    ui_->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    scene_->installEventFilter(this);
    ui_->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);

    // Create eventhandler & objectmanager objects

    auto gameEventHandler = std::make_shared<GameEventHandler>();
    auto objectManager = std::make_shared<ObjectManager>();
    gameEventHandler_ = gameEventHandler;
    objectManager_ = objectManager;

    // Add pictures

    addPixmaps();

    ui_->coinImg->setPixmap(pixmaps_.at("Coins"));
    ui_->foodImg->setPixmap(pixmaps_.at("Food"));
    ui_->woodImg->setPixmap(pixmaps_.at("Wood"));
    ui_->stoneImg->setPixmap(pixmaps_.at("Stone"));
    ui_->oreImg->setPixmap(pixmaps_.at("Ore"));
    ui_->buildCoinImg->setPixmap(pixmaps_.at("Coins"));
    ui_->buildWoodImg->setPixmap(pixmaps_.at("Wood"));
    ui_->buildStoneImg->setPixmap(pixmaps_.at("Stone"));
    ui_->buildOreImg->setPixmap(pixmaps_.at("Ore"));
    ui_->recruitCoinImg->setPixmap(pixmaps_.at("Coins"));
    ui_->recruitOreImg->setPixmap(pixmaps_.at("Ore"));
    ui_->recruitCoinImg2->setPixmap(pixmaps_.at("Coins"));
    ui_->recruitFoodImg->setPixmap(pixmaps_.at("Food"));

    // Widget config

    ui_->tabWidget->setTabEnabled(0, false);
    ui_->tabWidget->setTabEnabled(1, false);
    ui_->tabWidget->setTabEnabled(2, false);
    ui_->buildPanelButton->setVisible(false);
    ui_->recruitButton->setVisible(false);
    ui_->recruitButton->setToolTip("Recruit new warriors for your clan");
    ui_->recruitButton->setStyleSheet("background-color:darkGreen;" "color:white");
    ui_->endTurnButton->setStyleSheet("background-color:darkRed;" "color:white");
    ui_->confirmBuildButton->setStyleSheet("background-color:darkGreen;" "color:white");
    ui_->confirmRecruitButton->setStyleSheet("background-color:darkGreen;" "color:white");
    ui_->moveButton->setStyleSheet("background-color:#165581;" "color:white");
    ui_->turnLabel->setStyleSheet("color:blue");

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

    // Show welcome dialog

    welcomeDialog_->open();

}

MapWindow::~MapWindow() {

    delete ui_;

}

void MapWindow::setSize(int width, int height) {

    scene_->setSize(width, height);

}

void MapWindow::setScale(int scale) {

    scene_->setScale(scale);

}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj) {

    // TODO: Add removal from player and objectmanager?

    scene_->removeItem(obj);

}

void MapWindow::drawTile( std::shared_ptr<Course::TileBase> obj) {

    scene_->drawTile(obj);

}

void MapWindow::generateMap() {

    unsigned int seed = 123488;

    Course::WorldGenerator& worldGen = worldGen.getInstance();

    // Add tile types to the world generator
    worldGen.addConstructor<GrassTile>(200);
    worldGen.addConstructor<ForestTile>(75);
    worldGen.addConstructor<Swamp>(2);
    worldGen.addConstructor<Lake>(30);
    worldGen.addConstructor<Mountain>(4);

    // Execute world generation and pass tiles to objectManager
    worldGen.generateMap(static_cast<uint>(mapsizeX_), static_cast<uint>(mapsizeY_),
                         seed, objectManager_, gameEventHandler_);

}

void MapWindow::initializePlayer1() {

    // Create Player object

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    auto playerObject = std::make_shared<Player>("1", objects);
    players_.push_back(playerObject);
    auto player = players_.back();

    /* Create starting buildings and units for the player and add
     * them to the game
     */

    // TODO: Change tile to grass before building

    // Create objects

    std::shared_ptr<Headquarters> headquarters = std::make_shared<
            Headquarters>(gameEventHandler_, objectManager_, player,
                          1, HQ_BUILD_COST, HQ_PRODUCTION);

    std::shared_ptr<Farm> farm = std::make_shared<
            Farm>(gameEventHandler_, objectManager_, player,
                  1, FARM_BUILD_COST, FARM_PRODUCTION);


    std::shared_ptr<Infantry> infantry = std::make_shared<
            Infantry>(gameEventHandler_, objectManager_, player,
                  1, INFANTRY_RECRUITMENT_COST, INFANTRY_UPKEEP);


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

    /* Create starting buildings and units for the player and add
     * them to the game
     */

    // Create objects

    std::shared_ptr<Headquarters> headquarters = std::make_shared<
            Headquarters>(gameEventHandler_, objectManager_, player,
                          1, HQ_BUILD_COST, HQ_PRODUCTION);

    std::shared_ptr<Farm> farm = std::make_shared<
            Farm>(gameEventHandler_, objectManager_, player,
                  1, FARM_BUILD_COST, FARM_PRODUCTION);

    std::shared_ptr<Infantry> infantry = std::make_shared<
            Infantry>(gameEventHandler_, objectManager_, player,
                  1, INFANTRY_RECRUITMENT_COST, INFANTRY_UPKEEP);

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

    QString buildingToBuild = ui_->buildList->currentItem()->text(); // Building type
    std::shared_ptr<Course::TileBase> tile = selectedTile_;

    // Only build on own tiles
    if (tile->getOwner() != playerInTurn_) {
        return;
    }

    if (buildingToBuild == "Farm") {

        std::shared_ptr<Farm> farm = std::make_shared<
                Farm>(gameEventHandler_, objectManager_, playerInTurn_,
                      1, FARM_BUILD_COST, FARM_PRODUCTION);

        bool enoughResources = checkIfEnoughResources(FARM_BUILD_COST, playerInTurn_);

        if (not enoughResources) {

            showMessageBox(this, "Alert!",
                           "You don't have enough resources to"
                           " build this building. Gather some more"
                           " and try again.",
                           false);
            return;
        }

        objectManager_->addBuilding(farm);
        playerInTurn_->addObject(farm);
        tile->setOwner(playerInTurn_);
        tile->addBuilding(farm);
        farm->onBuildAction();

        gameEventHandler_->modifyResources(playerInTurn_, farm->BUILD_COST);

    } else if (buildingToBuild == "Outpost") {

        std::shared_ptr<Outpost> outpost = std::make_shared<Outpost>
                (gameEventHandler_, objectManager_, playerInTurn_,
                      1, OUTPOST_BUILD_COST, OUTPOST_PRODUCTION);

        bool enoughResources = checkIfEnoughResources(OUTPOST_BUILD_COST, playerInTurn_);

        if (not enoughResources) {

            showMessageBox(this, "Alert!",
                           "You don't have enough resources to"
                           " build this building. Gather some more"
                           " and try again.",
                           false);
            return;
        }

        objectManager_->addBuilding(outpost);
        playerInTurn_->addObject(outpost);
        tile->setOwner(playerInTurn_);
        tile->addBuilding(outpost);
        outpost->onBuildAction();

        gameEventHandler_->modifyResources(playerInTurn_, outpost->BUILD_COST);

    } else if (buildingToBuild == "Mine") {

        std::shared_ptr<Mine> mine = std::make_shared<Mine>
                (gameEventHandler_, objectManager_, playerInTurn_,
                      1, MINE_BUILD_COST, MINE_PRODUCTION);

        bool enoughResources = checkIfEnoughResources(MINE_BUILD_COST, playerInTurn_);

        if (not enoughResources) {

            showMessageBox(this, "Alert!",
                           "You don't have enough resources to"
                           " build this building. Gather some more"
                           " and try again.",
                           false);
            return;
        }

        objectManager_->addBuilding(mine);
        playerInTurn_->addObject(mine);
        tile->setOwner(playerInTurn_);
        tile->addBuilding(mine);
        mine->onBuildAction();

        gameEventHandler_->modifyResources(playerInTurn_, mine->BUILD_COST);

    } else if (buildingToBuild == "Lumber Mill") {

        std::shared_ptr<Lumbermill> lumbermill = std::make_shared<Lumbermill>
                (gameEventHandler_, objectManager_, playerInTurn_,
                      1, LUMBERMILL_BUILD_COST, LUMBERMILL_PRODUCTION);

        bool enoughResources = checkIfEnoughResources(LUMBERMILL_BUILD_COST, playerInTurn_);

        if (not enoughResources) {

            showMessageBox(this, "Alert!",
                           "You don't have enough resources to"
                           " build this building. Gather some more"
                           " and try again.",
                           false);
            return;
        }


        objectManager_->addBuilding(lumbermill);
        playerInTurn_->addObject(lumbermill);
        tile->setOwner(playerInTurn_);
        tile->addBuilding(lumbermill);
        lumbermill->onBuildAction();

        gameEventHandler_->modifyResources(playerInTurn_, lumbermill->BUILD_COST);

    }

    updateUI();
    updateHighScores();
    scene_->update();

}

void MapWindow::demolishBuilding(std::shared_ptr<Course::BuildingBase> building,
                                 std::shared_ptr<Course::TileBase> tile) {

    /* if the building is an outpost, change the ownership of owned tiles
     * around it to non-owned first. Do not change the ownership of tiles
     * which are owned by HQ or other outposts. Delete a building on a tile
     * which is owned only by the outpost being demolished. Prompt the user
     * if other buildings are affected.
     */
    bool found = false;
    bool result = true;
    std::shared_ptr<Player> enemy = nullptr;
    std::vector<std::shared_ptr<Course::GameObject>> alreadyOwnedTiles = {};
    std::vector<std::shared_ptr<Course::GameObject>> alreadyOwnedTilesEnemy = {};

    if (playerInTurn_->getName() == "1") {

        enemy = players_.at(1);

    } else {

        enemy = players_.at(0);

    }

    if (building->getType() == "Outpost") {

        /* create a prompt window to ask if the user really wants to continue.
         * Popup the prompt window only if the demolish is not done by
         * attacking (moveMode_ is on)
         */

        if (!moveMode_) {

            result = showMessageBox(this, "Warning!",
                                         "Every building on the land conquered only"
                                         " by this outpost will be removed. Are you"
                                         " sure you want to continue?",
                                         true);
        }


        if (result == false) {

            return;

        } else {

            // construct the alreadyOwnedTiles vectors

            for(auto object : playerInTurn_->getObjects()) {


                if (object == building) { // skip, if its the one being demolished
                    continue;
                } else if (object->getType() == "Headquarters" ||
                           object->getType() == "Outpost") {

                    std::vector<std::shared_ptr<Course::TileBase>> neighborTiles =
                            objectManager_->getTiles(object->getCoordinatePtr()->neighbours(2));

                    for (auto neighborTile : neighborTiles) {

                            alreadyOwnedTiles.push_back(neighborTile);
                    }

                    // also put the tile of the building itself into the vector
                    alreadyOwnedTiles.push_back(objectManager_->getTile(object->getCoordinate()));
                }
            }

            for(auto object : enemy->getObjects()) {


                if (object == building) { // skip, if its the one being demolished
                    continue;
                } else if (object->getType() == "Headquarters" ||
                           object->getType() == "Outpost") {

                    std::vector<std::shared_ptr<Course::TileBase>> neighborTiles =
                            objectManager_->getTiles(object->getCoordinatePtr()->neighbours(2));

                    for (auto neighborTile : neighborTiles) {

                            alreadyOwnedTilesEnemy.push_back(neighborTile);
                    }

                    // also put the tile of the building itself into the vector
                    alreadyOwnedTilesEnemy.push_back(objectManager_->getTile(object->getCoordinate()));
                }
            }

            // change ownership of tiles and remove necessary buildings

            for (auto neighbourTileCoord : building->getCoordinatePtr()->neighbours(2)) {

                std::shared_ptr<Course::TileBase> tileToChange =
                        objectManager_->getTile(neighbourTileCoord);

                /* do not do anything if the tile is not owned by the player,
                 * or the tile is "outside" of the coordinate system (nullptr)
                 * Change tiles according to the demolish type (attack/own building
                 * demolishing)
                 */
                if (!moveMode_) {

                    if (tileToChange == nullptr) {
                        continue;
                    } else if (tileToChange->getOwner() != playerInTurn_) {
                        continue;
                    }

                    /* check if the tile which is being changed is already owned
                     * by HQ or outpost.
                     */
                    for (auto ownedTile : alreadyOwnedTiles) {

                        if (ownedTile == tileToChange) {
                            found = true;
                        }
                    }

                } else {

                    if (tileToChange == nullptr) {
                        continue;
                    } else if (tileToChange->getOwner() == playerInTurn_) {
                        continue;
                    }

                    /* check if the tile which is being changed is already owned
                     * by enemy's HQ or outpost.
                     */
                    for (auto ownedTile : alreadyOwnedTilesEnemy) {

                        if (ownedTile == tileToChange) {
                            found = true;
                        }
                    }

                }




                /* remove ownership and buildings of the tiles conquered by the
                 * outpost if the user wants to.
                 */
                if (not found && tileToChange != nullptr) {

                    if(tileToChange->getBuildingCount() > 0) {
                        objectManager_->removeBuilding(tileToChange->getBuildings().at(0));

                    }
                    tileToChange->setOwner(nullptr);

                }

                found = false;
            }
        }

    }

    tile->removeBuilding(building);
    objectManager_->removeBuilding(building);

    /* update other outposts' conquered tiles in case some tiles were
     * partially acquired by the outpost which was demolished.
     */

    for (auto building : objectManager_->getAllBuildings()) {

        if (building->getType() == "Outpost") {
            building->onBuildAction();
        }

    }

    updateUI();
    updateHighScores();

}

void MapWindow::endTurn() {

    turn_ += 1;
    if (playerInTurn_->getName() == "2") {
        turnCount_ += 1;
    }

    // Apply building productions and unit upkeeps

    addProduction();

    // Add movement points to current player

    for (auto unit : objectManager_->getAllUnits()) {
        if (unit->getOwner() == playerInTurn_) {
            unit->resetMovement();
        }
    }

    // Change player in turn

    if (turn_ % 2 == 0) {
        playerInTurn_ = players_.at(1);
        ui_->turnLabel->setStyleSheet("color:red");
    } else {
        playerInTurn_ = players_.at(0);
        ui_->turnLabel->setStyleSheet("color:blue");
    }

    moveMode_ = false;
    viableTilesForMove_.clear();
    viableTilesForAttack_.clear();
    scene_->removeMoveMarkers();
    scene_->removeAttackMarkers();

    tilesToGiveBack_.clear();

    centerViewtoHQ();
    scene_->update();
    updateUI();

}

void MapWindow::addProduction() {

    // Add producted resources from all owned buildings

    for (auto object : playerInTurn_->getObjects()) {
        if (object->getType() == "Headquarters" ||
                object->getType() == "Farm" ||
                object->getType() == "Outpost" ||
                object->getType() == "Mine" ||
                object->getType() == "Lumbermill") {
            auto building = std::dynamic_pointer_cast<Course::BuildingBase>(object);
            gameEventHandler_->modifyResources(playerInTurn_, building->PRODUCTION_EFFECT);
        }
    }

    // Substract units' upkeep

    for (auto object : playerInTurn_->getObjects()) {
        if (object->getType() == "Infantry" ||
                object->getType() == "Archery" ||
                object->getType() == "Cavalry") {
            auto unit = std::dynamic_pointer_cast<UnitBase>(object);
            gameEventHandler_->modifyResources(playerInTurn_, unit->UPKEEP);
        }
    }

}

void MapWindow::updateResourceLabels() {

    int coins = 0;
    int food = 0;
    int wood = 0;
    int stone = 0;
    int ore = 0;

    // Add producted resources from all owned buildings

    for (auto object : playerInTurn_->getObjects()) {
        if (object->getType() == "Headquarters" ||
                object->getType() == "Farm" ||
                object->getType() == "Outpost" ||
                object->getType() == "Mine" ||
                object->getType() == "Lumbermill") {
            auto building = std::dynamic_pointer_cast<Course::BuildingBase>(object);
            auto resourceMap = building->getProduction();
            coins += resourceMap.at(Course::BasicResource::MONEY);
            food += resourceMap.at(Course::BasicResource::FOOD);
            wood += resourceMap.at(Course::BasicResource::WOOD);
            stone += resourceMap.at(Course::BasicResource::STONE);
            ore += resourceMap.at(Course::BasicResource::ORE);
        }
    }

    // Substract units' upkeep

    for (auto object : playerInTurn_->getObjects()) {
        if (object->getType() == "Infantry" ||
                object->getType() == "Archery" ||
                object->getType() == "Cavalry") {
            auto unit = std::dynamic_pointer_cast<UnitBase>(object);
            auto resourceMap = unit->UPKEEP;
            coins += resourceMap.at(Course::BasicResource::MONEY);
            food += resourceMap.at(Course::BasicResource::FOOD);
            wood += resourceMap.at(Course::BasicResource::WOOD);
            stone += resourceMap.at(Course::BasicResource::STONE);
            ore += resourceMap.at(Course::BasicResource::ORE);
        }
    }

    ui_->coinLabel->setText(QString::number(playerInTurn_->getMoney()) + " (" + QString::number(coins) + ")");
    ui_->foodLabel->setText(QString::number(playerInTurn_->getFood()) + " (" + QString::number(food) + ")");
    ui_->woodLabel->setText(QString::number(playerInTurn_->getWood()) + " (" + QString::number(wood) + ")");
    ui_->stoneLabel->setText(QString::number(playerInTurn_->getStone()) + " (" + QString::number(stone) + ")");
    ui_->oreLabel->setText(QString::number(playerInTurn_->getOre()) + " (" + QString::number(ore) + ")");

}

void MapWindow::centerViewtoHQ() {

    auto mapFocusLocation = std::make_shared<Course::Coordinate>(10, 10);

    // Find player HQ
    for (auto obj : playerInTurn_->getObjects()) {
        if (obj->getType() == "Headquarters") {
            mapFocusLocation = obj->getCoordinatePtr();
            qDebug() << "ID" << QString::fromStdString(std::to_string(obj->ID));
        }
    }

    double xCoordinate = mapFocusLocation->x();
    double yCoordinate = mapFocusLocation->y();
    ui_->graphicsView->centerOn(QPointF(xCoordinate * 60, yCoordinate * 60));

//    Course::Coordinate& locationRef = *mapFocusLocation;
//    selectedTile_ = objectManager_->getTile(locationRef);
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

void MapWindow::on_zoomInButton_clicked() {

    if (zoomLevel_ < 2) {
        ui_->graphicsView->scale(1.6, 1.6);
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
        ui_->graphicsView->scale(0.625, 0.625);
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

    // If tile has a building, button demolishes

    if (selectedTile_->getBuildingCount() < 1) {
        ui_->tabWidget->setTabEnabled(1, true);
        ui_->tabWidget->setCurrentIndex(1);
    } else {
        demolishBuilding(selectedTile_->getBuildings().at(0), selectedTile_);
    }

}

void MapWindow::on_confirmBuildButton_clicked() {

    ui_->tabWidget->setCurrentIndex(0);
    ui_->tabWidget->setTabEnabled(1, false);

    buildOnTile();

}

void MapWindow::on_buildList_itemDoubleClicked(QListWidgetItem *item) {

   on_confirmBuildButton_clicked();

}

void Aeta::MapWindow::on_buildList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {

    // Update build cost labels

    QString selectedBuilding = ui_->buildList->currentItem()->text(); // Building type
    Course::ResourceMap resourceMap = {};

    if (selectedBuilding == "Farm") {
        resourceMap = FARM_BUILD_COST;
    } else if (selectedBuilding == "Outpost") {
        resourceMap = OUTPOST_BUILD_COST;
    } else if (selectedBuilding == "Mine") {
        resourceMap = MINE_BUILD_COST;
    } else if (selectedBuilding == "Lumber Mill") {
        resourceMap = LUMBERMILL_BUILD_COST;
    }

    QString coins = QString::number(resourceMap.at(Course::BasicResource::MONEY));
    QString wood = QString::number(resourceMap.at(Course::BasicResource::WOOD));
    QString stone = QString::number(resourceMap.at(Course::BasicResource::STONE));
    QString ore = QString::number(resourceMap.at(Course::BasicResource::ORE));

    ui_->buildCoinLabel->setText(coins);
    ui_->buildWoodLabel->setText(wood);
    ui_->buildStoneLabel->setText(stone);
    ui_->buildOreLabel->setText(ore);

}

void Aeta::MapWindow::on_recruitList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {

    // Update recruitment cost labels

    QString selectedUnit = ui_->recruitList->currentItem()->text(); // Building type
    Course::ResourceMap recruitmentCostMap = {};
    Course::ResourceMapDouble upkeepCostMap = {};

    if (selectedUnit == "Infantry") {
        recruitmentCostMap = INFANTRY_RECRUITMENT_COST;
        upkeepCostMap = INFANTRY_UPKEEP;
    } else if (selectedUnit == "Archery") {
        recruitmentCostMap = ARCHERY_RECRUITMENT_COST;
        upkeepCostMap = ARCHERY_UPKEEP;
    } else if (selectedUnit == "Cavalry") {
        recruitmentCostMap = CAVALRY_RECRUITMENT_COST;
        upkeepCostMap = CAVALRY_UPKEEP;
    }

    QString coins = QString::number(recruitmentCostMap.at(Course::BasicResource::MONEY));
    QString ore = QString::number(recruitmentCostMap.at(Course::BasicResource::ORE));

    QString upkeepCoins = QString::number(upkeepCostMap.at(Course::BasicResource::MONEY));
    QString upkeepFood = QString::number(upkeepCostMap.at(Course::BasicResource::FOOD));

    ui_->recruitCoinLabel->setText(coins);
    ui_->recruitOreLabel->setText(ore);
    ui_->recruitCoinUpkeepLabel->setText(upkeepCoins + " / turn");
    ui_->recruitFoodLabel->setText(upkeepFood + " / turn");

}

void MapWindow::on_unitTextBox_editingFinished() {

    selectedUnit_->setName(ui_->unitTextBox->text().toStdString());

}

void Aeta::MapWindow::on_moveButton_clicked() {

    // Delete old markers
    scene_->removeMoveMarkers();
    scene_->removeAttackMarkers();

    if (moveMode_) {
        moveMode_ = false;
    } else {
        moveMode_ = true;
        onMoveModeActivate();
    }

    scene_->update();
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
            // If no buildings on tile
            ui_->tileHeaderLabel->setText(tileType);
            ui_->tileDescriptionLabel->setText(tileDesc);
            ui_->buildPanelButton->setVisible(true);
            ui_->buildPanelButton->setText("Build");
            ui_->buildPanelButton->setToolTip("Build a building on the this tile");
            ui_->buildPanelButton->setStyleSheet("background-color:darkGreen;" "color:white");

        }

        if (tile->getOwner() != nullptr) {

            // Update owner label

            QString playerName = QString::fromStdString(tile->getOwner()->getName());
            if (playerName == "1") {
                ui_->tileOwnerLabel->setText("Owned by " + player1UiName_);
                ui_->tileOwnerLabel->setStyleSheet("color:blue");
            } else {
                ui_->tileOwnerLabel->setText("Owned by " + player2UiName_);
                ui_->tileOwnerLabel->setStyleSheet("color:red");
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
            ui_->tileOwnerLabel->setStyleSheet("color:black");
            ui_->buildPanelButton->setVisible(false);
            ui_->recruitButton->setVisible(false);
        }

        // Update unit tab

        if (tile->getWorkers().size() > 0) {
            auto tileLocation = tile->getCoordinate();
            unit = objectManager_->getUnit(tileLocation);
            unitType = QString::fromStdString(unit->getType());

            // Update owner label

            QString playerName = QString::fromStdString(unit->getOwner()->getName());
            if (playerName == "1") {
                ui_->unitOwnerLabel->setText("Owned by " + player1UiName_);
                ui_->unitOwnerLabel->setStyleSheet("color:blue");
            } else {
                ui_->unitOwnerLabel->setText("Owned by " + player2UiName_);
                ui_->unitOwnerLabel->setStyleSheet("color:red");
            }

            ui_->unitTypeLabel->setText("Type: " + unitType);
            ui_->unitTextBox->setText(QString::fromStdString(unit->getName()));
            ui_->healthBar->setMaximum(unit->getMaxHealth());
            ui_->healthBar->setValue(unit->getHealth());
            ui_->healthValueLabel->setText(QString::number(unit->getHealth()));
            ui_->movementPointNumber->setText(QString::fromStdString(std::to_string(unit->getMovement())));
            ui_->damageNumberLabel->setText(QString::fromStdString(std::to_string(unit->getDamage())));
            ui_->rangeNumberLabel->setText(QString::fromStdString(std::to_string(unit->getRange())));

            if (playerInTurn_ != unit->getOwner()) {
                ui_->moveButton->setVisible(false);
            } else {
                ui_->moveButton->setVisible(true);
            }

            // Update move button

            if (moveMode_) {
                ui_->moveButton->setStyleSheet("background-color:yellow;" "color:black");
                ui_->moveButton->setText("Cancel move");
            } else {
                ui_->moveButton->setStyleSheet("background-color:#165581;" "color:white");
                ui_->moveButton->setText("Move / Attack");
            }

            // Gray out the button when movement points run out
            if (selectedUnit_->getMovement() == 0) {
                ui_->moveButton->setEnabled(false);
                ui_->moveButton->setStyleSheet("background-color:gray;" "color:black");
                ui_->moveButton->setToolTip("Your unit is too tired to continue");
            } else {
                ui_->moveButton->setEnabled(true);
                ui_->moveButton->setToolTip("Move the unit or attack enemy units");
            }

            // Set UI picture for unit

            unitPic = pixmaps_.at(unit->getType());

            ui_->unitImgLabel->setPixmap(unitPic);

            ui_->tabWidget->setTabEnabled(2, true);
            ui_->tabWidget->setCurrentIndex(2);
        } else {
            ui_->tabWidget->setTabEnabled(2, false);
            ui_->tabWidget->setCurrentIndex(0);
        }

        ui_->tileImgLabel->setPixmap(pic);

        // Hide build button if build not allowed

        if (selectedTile_->getType() == "Mountain" ||
                selectedTile_->getType() == "Lake" ||
                selectedTile_->getType() == "Swamp") {
            ui_->buildPanelButton->setVisible(false);
        }

    } // End of 'if no tile selected'

    // Update turn labels

    ui_->turnCountLabel->setText("Turn: " + QString::fromStdString(std::to_string(turnCount_)));
    QString playerName = QString::fromStdString(playerInTurn_->getName());

    if (playerName == "1") {
        ui_->turnLabel->setText(player1UiName_ + "'s turn");
    } else {
        ui_->turnLabel->setText(player2UiName_ + "'s turn");
    }

    updateResourceLabels();

}

void MapWindow::gameOver() {

    // Get player names

    QString winPlayerName = "winner";
    QString losePlayerName = "loser";

    if (playerInTurn_->getName() == "1") {
        winPlayerName = player1UiName_;
        losePlayerName = player2UiName_;
    } else {
        winPlayerName = player2UiName_;
        losePlayerName = player1UiName_;
    }

    // Send high scores to winDialog
    emit highScore(turnCount_, winPlayerName, losePlayerName, player1UiName_, player2UiName_,
                   player1TilesMax_, player2TilesMax_, player1BuildingsMax_,
                   player2BuildingsMax_, player1ArmyMax_, player2ArmyMax_);

    winDialog_->open();

}

bool MapWindow::checkIfEnoughResources(const Course::ResourceMap &resourcesRequired,
                                       const std::shared_ptr<Player> &player) {

    for (auto resource : player->getResources()) {

        if (abs(resourcesRequired.at(resource.first)) > resource.second) {
            return false;
        }

    }
    return true;

}

bool MapWindow::showMessageBox(QWidget *parent,
                               const QString &windowTitle,
                               const QString &windowMessage,
                               const bool &cancelButtonMode) {
    auto msgBox = std::make_shared<QMessageBox>(parent);
    msgBox->setWindowTitle(windowTitle);
    msgBox->setText(windowMessage);
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    // set cancelButton inactive if needed
    if (not cancelButtonMode) {
       msgBox->button(QMessageBox::Cancel)->setVisible(false);
    }

    int result = msgBox->exec();

    if (result == QMessageBox::Ok) {
        return true;
    } else {
        return false;
    }

}

void MapWindow::showTextAnimation(const QString &text, const Course::Coordinate &startPosition,
                                  const QColor &color) {

    // values for the movement of the animation
    QPoint location(startPosition.x() * mapScale_, startPosition.y() * mapScale_ - 1);
    QPoint endLocation(location.x(), location.y() - 60); // 60 pixels up

    // create a object to show
    QGraphicsTextItem *textItem = new QGraphicsTextItem();
    textItem->setPlainText(text);
    textItem->setDefaultTextColor(color);
    textItem->setPos(location);
    scene_->addItem(textItem);

    // make an animation for the textItem
    QPropertyAnimation *anim = new QPropertyAnimation(textItem, "pos");
    anim->setStartValue(textItem->pos());
    // end position for the animation
    anim->setEndValue(endLocation);
    anim->setDuration(1500);
    anim->start();

    // deleting the text object after animation
    connect(anim, SIGNAL(finished()), textItem, SLOT(deleteLater()));


}

void MapWindow::updateHighScores() {

    // Get tile counts

    int player1Tiles = 0;
    int player2Tiles = 0;
    for (auto tile : objectManager_->getAllTiles()) {
        if (tile->getOwner() == players_.at(0)) {
            player1Tiles += 1;
        } else if (tile->getOwner() == players_.at(1)) {
            player2Tiles += 1;
        }
    }

    // Get building counts

    int player1Buildings = 0;
    int player2Buildings = 0;
    for (auto building : objectManager_->getAllBuildings()) {
        if (building->getOwner() == players_.at(0)) {
            player1Buildings += 1;
        } else if (building->getOwner() == players_.at(1)) {
            player2Buildings += 1;
        }
    }

    // Get army sizes

    int player1Army = 0;
    int player2Army = 0;
    for (auto unit : objectManager_->getAllUnits()) {
        if (unit->getOwner() == players_.at(0)) {
            player1Army += 1;
        } else if (unit->getOwner() == players_.at(1)) {
            player2Army += 1;
        }
    }

    // Check if new high score

    if (player1Tiles > player1TilesMax_) {
        player1TilesMax_ = player1Tiles;
    }

    if (player2Tiles > player2TilesMax_) {
        player2TilesMax_ = player2Tiles;
    }

    if (player1Buildings > player1BuildingsMax_) {
        player1BuildingsMax_ = player1Buildings;
    }

    if (player2Buildings > player2BuildingsMax_) {
        player2BuildingsMax_ = player2Buildings;
    }

    if (player1Army > player1ArmyMax_) {
        player1ArmyMax_ = player1Army;
    }

    if (player2Army > player2ArmyMax_) {
        player2ArmyMax_ = player2Army;
    }

}

std::shared_ptr<Course::TileBase> MapWindow::cutForest(
        const std::shared_ptr<Course::TileBase> &tile) {

    std::shared_ptr<Course::Coordinate> coordPtr =
            tile->getCoordinatePtr();
    Course::Coordinate& coordinate = *coordPtr;
    std::shared_ptr<Player> tileOwner =
            std::dynamic_pointer_cast<Player>(tile->getOwner());

    /* Create a new basic grasstile. Put it on the forests place, play
     * wood gain animation and draw appropriately owned grass on the
     * forests place. Add the resources to the player and update UI.
     */

    auto grassTile = std::make_shared<GrassTile>(
                coordinate, gameEventHandler_, objectManager_, 1, 1,
                Course::ConstResourceMaps::GRASSLAND_BP);

    // first set the right owner for the new grassTile

    std::size_t notInTurn; // vector location

    if(playerInTurn_->getName() == "1") {
        notInTurn = 1;
    } else {
        notInTurn = 0;
    }

    if (tileOwner != nullptr) {

        if (tileOwner == playerInTurn_) {
            grassTile->setOwner(playerInTurn_);
        } else {
            grassTile->setOwner(players_.at(notInTurn));
        }

    }

    objectManager_->removeTile(tile);
    scene_->removeItem(tile);
    objectManager_->addTiles({grassTile});
    scene_->drawTile(grassTile);

    showTextAnimation("+15 wood!", grassTile->getCoordinate(),
                      Qt::green);
    gameEventHandler_->modifyResource(playerInTurn_,
                                      Course::BasicResource::WOOD,
                                      15);
    updateUI();

    // return new tile in right form

    auto newTilePtr = std::dynamic_pointer_cast<Course::TileBase>(grassTile);

    return newTilePtr;

}

bool MapWindow::attackHQ(const std::shared_ptr<Course::TileBase> &tile, const std::shared_ptr<UnitBase> &attacker) {

    std::shared_ptr<Headquarters> HQ = std::dynamic_pointer_cast<Headquarters>(tile->getBuildings().at(0));
    HQ->changeHitPoints((attacker->getDamage()) * (-1));
    selectedUnit_->setMovement(0);

    if (HQ->getHitPoints() <= 0) {
        return true; // HQ has been destroyed
    } else {
        return false;
    }

}

void MapWindow::onMoveModeActivate() {

    viableTilesForMove_.clear();
    viableTilesForAttack_.clear();
    scene_->removeMoveMarkers();
    scene_->removeAttackMarkers();
    scene_->update();

    if (selectedTile_->getWorkerCount() > 0) {
        selectedUnit_ = objectManager_->getUnit(selectedTile_->getCoordinate());
    }

    int movementPoints = selectedUnit_->getMovement();
    int attackRange = selectedUnit_->getRange();
    std::vector<Course::Coordinate> neighborCoordinates = {};

    if (movementPoints > 0) {
        neighborCoordinates = selectedTile_->getCoordinate().neighbours(1);
    } else {
        qDebug() << "No movement points";
    }

    std::vector<std::shared_ptr<Course::TileBase>> neighborTiles =
            objectManager_->getTiles(neighborCoordinates);

    // Add free tiles to movevector

    for (auto tile : neighborTiles) {

        if (((tile->getType() == "Swamp") && (movementPoints < 2))
                || (tile->getType() == "Mountain")
                || (tile->getType() == "Lake")
                || ((tile->getWorkerCount() > 0) && (tile->getOwner() == playerInTurn_))) {
            continue;
        } else {

            if ((tile->getWorkerCount() > 0)) {
                continue;
            } else {
                viableTilesForMove_.push_back(tile);
            }

        }
    }

    // Add enemy units and buildings to attackvector

    if (movementPoints > 0) {

        neighborCoordinates =
                selectedTile_->getCoordinate().neighbours(attackRange);
        std::vector<std::shared_ptr<Course::TileBase>> neighborTiles =
                objectManager_->getTiles(neighborCoordinates);

        for (auto tile : neighborTiles) {

            if ((tile->getWorkerCount() > 0)
                    && (tile->getWorkers().at(0)->getOwner() != playerInTurn_)) {
                viableTilesForAttack_.push_back(tile);
            } else if ((tile->getBuildingCount() > 0) &&
                       (tile->getBuildings().at(0)->getOwner() != playerInTurn_)) {
                viableTilesForAttack_.push_back(tile);
            }

        }
    }

    drawMovementMarkers(viableTilesForMove_);
    drawAttackMarkers(viableTilesForAttack_);

}

void MapWindow::drawMovementMarkers(std::vector<std::shared_ptr<Course::TileBase>> tiles) {

    for (auto tile : tiles) {
        scene_->drawMoveMarker(tile);
    }

}

void MapWindow::drawAttackMarkers(std::vector<std::shared_ptr<Course::TileBase>> tiles) {

    for (auto tile : tiles) {
        scene_->drawAttackMarker(tile);
    }

}

bool MapWindow::moveUnit(const std::shared_ptr<Course::TileBase> &tile) {

    viableTilesForMove_.clear();
    viableTilesForAttack_.clear();
    scene_->removeMoveMarkers();
    scene_->removeAttackMarkers();

    int requiredMovementPoints = 1;
    bool moveIsAttackOnly = false;

    if (tile->getType() == "Swamp") {
        requiredMovementPoints = 2;
    }

    // If no units on tile
    if (tile->getWorkerCount() == 0) {

        // If enemy tile
        if (tile->getOwner() != selectedUnit_->getOwner()) {

            // Destroy possible enemy building
            if (tile->getBuildingCount() > 0) {
                auto building = tile->getBuildings().at(0);

                // Attack HQ
                if (building->getType() == "Headquarters") {
                    bool HQDestroyed = attackHQ(tile, selectedUnit_);
                    showTextAnimation("-" +
                                      QString::number(selectedUnit_->getDamage()),
                                      tile->getCoordinate(), Qt::red);
                    qDebug() << "HQ took damage";
                    moveIsAttackOnly = true;

                    // HQ Destroyed -> Game won
                    if (HQDestroyed) {
                        demolishBuilding(building, tile);
                        qDebug() << "HQ DESTROYED";
                        moveIsAttackOnly = false;
                        gameOver();
                    }

                } else {
                    qDebug() << "ENEMY BUILDING DESTROYED";
                    demolishBuilding(building, tile);
                    showTextAnimation(QString::fromStdString(building->getType())
                                      + " destroyed!",
                                      tile->getCoordinate(), Qt::red);
                    moveIsAttackOnly = true;
                    selectedUnit_->setMovement(0);
                }
            }
        }

        // Move the unit as not attacking
        if (!moveIsAttackOnly) {

            auto coordinate = selectedTile_->getCoordinate();

//            if (tile->getType() == "Forest") {
//                auto newTile = cutForest(tile);

//            }

            selectedUnit_->setCoordinate(coordinate);
            selectedTile_->removeWorker(selectedUnit_);
            tile->addWorker(selectedUnit_);
            qDebug() << "Moved to: " << coordinate.x() << coordinate.y();



            if (selectedUnit_->getMovement() >= requiredMovementPoints) {
                selectedUnit_->changeMovement(-requiredMovementPoints);
            } else {
                return false;
            }

        }

    } else {
        // Attack enemy unit
        qDebug() << "Tile occupied by unit";

        std::shared_ptr<UnitBase> otherUnit = objectManager_->getUnit(tile->getCoordinate());

        // If enemy
        if (otherUnit->getOwner() != selectedUnit_->getOwner()) {
            bool enemyDied = selectedUnit_->attackUnit(otherUnit);

            qDebug() << "Enemy unit took damage";

            selectedUnit_->setMovement(0);

            // Enemy unit dies and show animation
            if (enemyDied) {

                showTextAnimation(QString::fromStdString(otherUnit->getName())
                                  + " died!", otherUnit->getCoordinate(), Qt::red);

                tile->removeWorker(otherUnit);
                objectManager_->removeUnit(otherUnit);
                qDebug() << "Enemy unit died";

            } else {
                showTextAnimation("-" + QString::number(selectedUnit_->getDamage()),
                                  otherUnit->getCoordinate(), Qt::red);
            }
        }
    }

    moveMode_ = false;
    selectedTile_ = tile;
    scene_->update();
    updateUI();
    return true;

}

void MapWindow::recruitUnit() {

    // Unit type and location setup.

    QString unitToRecruit = ui_->recruitList->currentItem()->text();
    Course::Coordinate location(0,0);

    // spawn units on the headquarter tile. Location depends on player.

    if(playerInTurn_->getName() == "1") {
        location = player1HQ_->getCoordinate();
    } else {
        location = player2HQ_->getCoordinate();
    }

    std::shared_ptr<Course::TileBase> tileToSpawn = objectManager_->getTile(location);

    // if there is an unit already, ask the player to move the unit first

    if (tileToSpawn->getWorkerCount() > 0) {

        showMessageBox(this,
                       "Alert",
                       "You got an unit spawned on HQ already."
                       " Please move the unit first.", false);

        return;
    }


    if (unitToRecruit == "Infantry") {

        std::shared_ptr<Infantry> infantry = std::make_shared<
                Infantry>(gameEventHandler_, objectManager_, playerInTurn_,
                      1, INFANTRY_RECRUITMENT_COST, INFANTRY_UPKEEP);

        bool enoughResources = checkIfEnoughResources(INFANTRY_RECRUITMENT_COST, playerInTurn_);

        if (not enoughResources) {

            showMessageBox(this, "Alert!",
                           "You don't have enough resources to"
                           " recruit this unit. Gather some more"
                           " and try again.",
                           false);
            return;
        }


        objectManager_->addUnit(infantry);
        playerInTurn_->addObject(infantry);
        infantry->setOwner(playerInTurn_);
        tileToSpawn->addWorker(infantry);
        //infantry->onBuildAction();

        gameEventHandler_->modifyResources(playerInTurn_, infantry->RECRUITMENT_COST);
        selectedUnit_ = infantry;

    } else if (unitToRecruit == "Archery") {

        std::shared_ptr<Archery> archery = std::make_shared<
                Archery>(gameEventHandler_, objectManager_, playerInTurn_,
                      1, ARCHERY_RECRUITMENT_COST, ARCHERY_UPKEEP);

        bool enoughResources = checkIfEnoughResources(ARCHERY_RECRUITMENT_COST, playerInTurn_);

        if (not enoughResources) {

            showMessageBox(this, "Alert!",
                           "You don't have enough resources to"
                           " recruit this unit. Gather some more"
                           " and try again.",
                           false);
            return;
        }

        objectManager_->addUnit(archery);
        playerInTurn_->addObject(archery);
        archery->setOwner(playerInTurn_);
        tileToSpawn->addWorker(archery);
        //archery->onBuildAction();

        gameEventHandler_->modifyResources(playerInTurn_, archery->RECRUITMENT_COST);
        selectedUnit_ = archery;

    } else if (unitToRecruit == "Cavalry") {

        std::shared_ptr<Cavalry> cavalry = std::make_shared<
                Cavalry>(gameEventHandler_, objectManager_, playerInTurn_,
                      1, CAVALRY_RECRUITMENT_COST, CAVALRY_UPKEEP);

        bool enoughResources = checkIfEnoughResources(CAVALRY_RECRUITMENT_COST, playerInTurn_);

        if (not enoughResources) {

            showMessageBox(this, "Alert!",
                           "You don't have enough resources to"
                           " recruit this unit. Gather some more"
                           " and try again.",
                           false);
            return;
        }

        objectManager_->addUnit(cavalry);
        playerInTurn_->addObject(cavalry);
        cavalry->setOwner(playerInTurn_);
        tileToSpawn->addWorker(cavalry);
        //cavalry->onBuildAction();

        gameEventHandler_->modifyResources(playerInTurn_, cavalry->RECRUITMENT_COST);
        selectedUnit_ = cavalry;

    }

    updateUI();
    updateHighScores();
    scene_->update();

}

bool MapWindow::eventFilter(QObject *object, QEvent *event) {

    if (object == &*scene_ && event->type() == QEvent::GraphicsSceneMousePress) {

        if (moveMode_) {

            uint tileID = scene_->tileClicked(event, false);
            qDebug() << "Got tileID for moving: " << tileID;
            std::shared_ptr<Course::TileBase> toTile = objectManager_->getTile(tileID);

            // Move unit if possible
            for (auto tile : viableTilesForMove_) {
                if (tile->ID == tileID) {
                    if (moveUnit(toTile)) {
                        scene_->tileClicked(event, true);

                        // Continue move if points left
                        if (selectedUnit_->getMovement() > 0) {
                            on_moveButton_clicked();
                        }

                    } else {
                        onMoveModeActivate();
                    }
                } else {
                    onMoveModeActivate();
                }
            }

            for (auto tile : viableTilesForAttack_) {

                if (tile->ID == tileID) {

                    if (moveUnit(toTile)) {
                        scene_->tileClicked(event, true);
                        break;
                    } else {
                        on_moveButton_clicked();
                    }

                } else {
                    onMoveModeActivate();
                }
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

void MapWindow::addPixmaps() {

    std::vector<std::string> types = {"Archery", "Archery1", "Archery2",
                                      "Archery1Free", "Archery1Owned",
                                      "Archery2Free", "Archery2Owned",
                                      "Cavalry", "Cavalry1", "Cavalry2",
                                      "Cavalry1Free",
                                      "Cavalry1Owned", "Cavalry2Free",
                                      "Cavalry2Owned",
                                      "Coins", "Farm", "Farm1", "Farm2",
                                      "Food", "Forest", "Forest1",
                                      "Forest2", "Grass", "Grass1",
                                      "Grass2", "Headquarters",
                                      "Headquarters1", "Headquarters2",
                                      "Infantry", "Infantry1", "Infantry2",
                                      "Infantry1Free", "Infantry1Owned",
                                      "Infantry2Free", "Infantry2Owned",
                                      "Lake", "Lake1", "Lake2",
                                      "Lumbermill", "Lumbermill1",
                                      "Lumbermill2", "Mine", "Mine1",
                                      "Mine2", "Mountain", "Mountain1",
                                      "Mountain2",
                                      "Ore", "Outpost", "Outpost1",
                                      "Outpost2", "Stone", "Swamp", "Swamp1",
                                      "Swamp2", "Wood", "Workforce"};

    for (auto mapItemType : types) {
        QString filePath = QString::fromStdString(":/pictures/pictures/"
                                                  + mapItemType + ".png");
        QPixmap image(filePath);
        pixmaps_.insert({mapItemType, image});
    }

}

} // namespace Aeta
