#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "graphics/simplemapitem.h"
#include "core/resourcemaps.h"
#include "core/worldgenerator.h"
#include "grasstile.h"
#include "foresttile.h"
#include "headquarters.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"

#include <memory>
#include <math.h>
#include <iostream>

namespace Aeta {

MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    ui_(new Ui::MapWindow),
    scene_(new GameScene(this)) {

    ui_->setupUi(this);

    // Set scene
    Aeta::GameScene* sgs_rawptr = scene_.get();
    ui_->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));

    // Widget config
    ui_->tabWidget->setTabEnabled(1, true);
    ui_->endTurnButton->setStyleSheet("background-color:darkRed;" "color:white");

    // Draw pictures
    QPixmap GrassPic(":/pictures/pictures/grasstile.png");
    QPixmap HQPic(":/pictures/pictures/headquarters.png");
    QPixmap archerPic(":/pictures/pictures/archer.png");
    ui_->buildingImgLabel->setPixmap(HQPic);
    ui_->tileImgLabel->setPixmap(GrassPic);
    ui_->unitImgLabel->setPixmap(archerPic);

    // Create eventhandler & objectmanager objects
    auto gameEventHandler = std::make_shared<Aeta::GameEventHandler>();
    auto objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler_ = gameEventHandler;
    objectManager_ = objectManager;

    /* Build map and setup the player objects and the starting buildings
     * for both
     */

    generateMap();
    drawMap();
    initializeStart(player1Name_);
    //initializeStart(player2Name_);

    // DEBUG ###########################################################################

    //Player:

    QString name = QString::fromStdString(players_.at(0)->getName());
    qDebug () << "Players name: " << name;

    qDebug () << "Buildingcount for player after initialize: " << players_.at(0)->getObjects().size();

    //Tile:

    auto location = std::make_shared<Course::Coordinate>(2, 2);
    Course::Coordinate& locationRef = *location;

    auto tileObject = objectManager_->getTile(locationRef);

    QString tileType = QString::fromStdString(tileObject->getType());
    qDebug () << "Tile type: " << tileType;

    if (tileObject->getOwner() == nullptr) {
        qDebug () << "Tile has no owner.";
    } else {
        QString owner = QString::fromStdString(tileObject->getOwner()->getName());
        qDebug () << "Tiles owner: " << owner;
    }

    qDebug () << "Tiles buildingcount after initialize: " << tileObject->getBuildingCount();

    // DEBUG ###########################################################################

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

    // Generate HQ and add it to a tile and add the player as its owner
    // TODO: headquarters disappearing..

    std::shared_ptr<Headquarters> headquarters = std::make_shared<
            Headquarters>(gameEventHandler_, objectManager_, player,
                          1, Course::ConstResourceMaps::HQ_BUILD_COST,
                          Course::ConstResourceMaps::HQ_PRODUCTION);


    player->addObject(headquarters);

    auto location = std::make_shared<Course::Coordinate>(2, 2);
    Course::Coordinate& locationRef = *location;
    auto tileObject = objectManager_->getTile(locationRef);

    tileObject->addBuilding(headquarters);

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
            drawItem(tile);
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

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj) {

    scene_->drawItem(obj);

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

} // namespace Aeta
