#include "core/resourcemaps.h"
#include "core/worldgenerator.h"

#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "grasstile.h"
#include "foresttile.h"
#include "headquarters.h"
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

    // Widget config

    ui_->tabWidget->setTabEnabled(1, true);
    ui_->endTurnButton->setStyleSheet("background-color:darkRed;" "color:white");

    // Add pictures

    QPixmap GrassPic(":/pictures/pictures/grasstile.png");
    QPixmap HQPic(":/pictures/pictures/headquarters.png");
    QPixmap archerPic(":/pictures/pictures/archer.png");
    ui_->buildingImgLabel->setPixmap(HQPic);
    ui_->tileImgLabel->setPixmap(GrassPic);
    ui_->unitImgLabel->setPixmap(archerPic);

    // Create eventhandler & objectmanager objects

    auto gameEventHandler = std::make_shared<GameEventHandler>();
    auto objectManager = std::make_shared<ObjectManager>();
    gameEventHandler_ = gameEventHandler;
    objectManager_ = objectManager;

    // connect signals and slots FIX

    //QObject::connect(&*scene_, &GameScene::sendObjectId, &*gameEventHandler_, &GameEventHandler::clickOnTile);

    /* Build map and setup the player objects and the starting buildings
     * for both
     */

    generateMap();
    drawMap();
    initializeStart(player1Name_);
    //initializeStart(player2Name_)


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

void MapWindow::initializeStart(std::string playerName) {

    // Create Player object

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    auto playerObject = std::make_shared<Player>(playerName, objects);
    players_.push_back(playerObject);
    auto player = players_.back();

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

    objectManager_ -> addBuilding(farm);
    player->addObject(farm);

    locationRef.set_x(1);
    locationRef.set_y(2);
    tileObject = objectManager_->getTile(locationRef);

    tileObject->setOwner(player);
    tileObject->addBuilding(farm);

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

//void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
//{
//    scene_->updateItem(obj);
//}

//void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
//{
//    scene_->removeItem(obj);
//}

void MapWindow::drawTile( std::shared_ptr<Course::TileBase> obj) {

    scene_->drawTile(obj);

}

void MapWindow::mouseWheelEventHandler(QGraphicsSceneWheelEvent *mouseWheelEvent) {

    int degrees = mouseWheelEvent->delta();
    int steps = degrees / 10;

    if (steps > 0) {
        ui_->graphicsView->scale(steps * 1.1, steps * 1.1);
    } else {
        ui_->graphicsView->scale(steps * 0.909090909, steps * 0.909090909);
    }

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

void MapWindow::updateUI(uint tileID) {

    // Get gameobjects on tile
    std::shared_ptr<Course::TileBase> tile = objectManager_->getTile(tileID);
    std::shared_ptr<Course::BuildingBase> building = nullptr;
    std::shared_ptr<Course::WorkerBase> unit = nullptr;

    // Get names and descriptions
    QString tileType = QString::fromStdString(tile->getType());
    QString tileDesc = QString::fromStdString(tile->getDescription("basic"));
    QString buildingType = "No buildings";
    QString buildingDesc = "Null";
    QString unitType = "Null_unit";

    if (tile->getBuildings().size() > 0) {
        building = tile->getBuildings().at(0);
        buildingType = QString::fromStdString(building->getType());
        buildingDesc = QString::fromStdString(building->getDescription("basic"));
        ui_->tabWidget->setTabEnabled(1, true);
    } else {
        ui_->tabWidget->setTabEnabled(1, false);
    }

    if (tile->getWorkers().size() > 0) {
        unit = tile->getWorkers().at(0);
        unitType = QString::fromStdString(unit->getType());
        ui_->tabWidget->setTabEnabled(2, true);
    } else {
        ui_->tabWidget->setTabEnabled(2, false);
    }

    ui_->tileHeaderLabel->setText(tileType);
    ui_->tileDescriptionLabel->setText(tileDesc);
    ui_->buildingHeaderLabel->setText(buildingType);
    ui_->buildingDescriptionLabel->setText(buildingDesc);
    ui_->unitTypeLabel->setText("Type: " + unitType);
}

bool MapWindow::eventFilter(QObject *object, QEvent *event) {

    if (object == &*scene_ && event->type() == QEvent::GraphicsSceneMousePress) {
            qDebug() << "Jee se toimii, nyt kutsu";
            uint tileID = scene_->tileClicked(event);
            qDebug() << "Got tileID: " << tileID;
            updateUI(tileID);
            return true;
    }

    return false;

}

} // namespace Aeta
