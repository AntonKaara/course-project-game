#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "graphics/simplemapitem.h"
#include "core/resourcemaps.h"
#include "core/worldgenerator.h"

#include "grasstile.h"
#include "tiles/forest.h"

#include "gameeventhandler.hh"
#include "objectmanager.hh"

#include <memory>
#include <math.h>
#include <iostream>

MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    ui_(new Ui::MapWindow),
    scene_(new Aeta::GameScene(this))
{
    ui_->setupUi(this);

    // Set scene
    Aeta::GameScene* sgs_rawptr = scene_.get();
    ui_->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));

    // Widget config
    ui_->tabWidget->setTabEnabled(1, true);

    // Create eventhandler & objectmanager objects
    auto gameEventHandler = std::make_shared<Aeta::GameEventHandler>();
    auto objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler_ = gameEventHandler;
    objectManager_ = objectManager;

    generateMap();
    drawMap(1);
}

MapWindow::~MapWindow()
{
    delete ui_;
}

void MapWindow::generateMap()
{
    int seed = 123488; // Add random generation?

    Course::WorldGenerator& worldGen = worldGen.getInstance();
    worldGen.addConstructor<Aeta::GrassTile>(80);
    worldGen.addConstructor<Course::Forest>(0);
    worldGen.generateMap(mapsizeX_, mapsizeY_, seed, objectManager_, gameEventHandler_);
}

void MapWindow::drawMap(double scale) {
    setSize(mapsizeX_, mapsizeY_);
    setScale(scale);

    // Coordinate-object
    auto location = std::make_shared<Course::Coordinate>(0, 0);
    Course::Coordinate& locationref = *location;

    // Draw each tile
    int x = 0;
    int y = 0;
    while (x < mapsizeX_) {
        while (y < mapsizeY_){
            auto tile = objectManager_->getTile(locationref);
            drawItem(tile);
            y++;
            locationref.set_y(y);
        }
        x++;
        locationref.set_x(x);
        y = 0;
        locationref.set_y(y);
    }
}

void MapWindow::setSize(int width, int height)
{
    scene_->setSize(width, height);
}

void MapWindow::setScale(double scale)
{
    scene_->setScale(scale);
}

void MapWindow::resize()
{
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

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    scene_->drawItem(obj);
}

void MapWindow::on_zoomInButton_clicked()
{
    if (mapScale_ < 3) {
        mapScale_ = mapScale_ + 1;
        drawMap(mapScale_);
    }

    if (mapScale_ == 1) {
        ui_->zoomInButton->setEnabled(true);
        ui_->zoomOutButton->setEnabled(false);
    } else if (mapScale_ == 2) {
        ui_->zoomInButton->setEnabled(true);
        ui_->zoomOutButton->setEnabled(true);
    } else if (mapScale_ == 3) {
        ui_->zoomInButton->setEnabled(false);
        ui_->zoomOutButton->setEnabled(true);
    }
}

void MapWindow::on_zoomOutButton_clicked()
{
    if (mapScale_ > 1) {
        mapScale_ = mapScale_ - 1;
        drawMap(mapScale_);
    }

    if (mapScale_ == 1) {
        ui_->zoomInButton->setEnabled(true);
        ui_->zoomOutButton->setEnabled(false);
    } else if (mapScale_ == 2) {
        ui_->zoomInButton->setEnabled(true);
        ui_->zoomOutButton->setEnabled(true);
    } else if (mapScale_ == 3) {
        ui_->zoomInButton->setEnabled(false);
        ui_->zoomOutButton->setEnabled(true);
    }
}
