#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "graphics/simplemapitem.h"
#include "core/resourcemaps.h"
#include "core/worldgenerator.h"

#include "grasstile.h"
#include "tiles/grassland.h"
#include "tiles/forest.h"

#include "gameeventhandler.hh"
#include "objectmanager.hh"

#include <memory>
#include <math.h>
#include <iostream>

MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    ui_(new Ui::MapWindow),
    //m_simplescene(new Course::SimpleGameScene(this))
    scene_(new Aeta::GameScene(this))
{
    ui_->setupUi(this);

    Aeta::GameScene* sgs_rawptr = scene_.get();

    ui_->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    ui_->tabWidget->setTabEnabled(1, true);

    auto gameEventHandler = std::make_shared<Aeta::GameEventHandler>();
    auto objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler_ = gameEventHandler;
    objectManager_ = objectManager;

    generateMap();
}

MapWindow::~MapWindow()
{
    delete ui_;
}

void MapWindow::generateMap()
{
    int sizeX = 20;
    int sizeY = 20;
    int seed = 123488;

    Course::WorldGenerator& worldGen = worldGen.getInstance();
    worldGen.addConstructor<Aeta::GrassTile>(80);
    worldGen.addConstructor<Course::Forest>(0);
    worldGen.generateMap(sizeX, sizeY, seed, objectManager_, gameEventHandler_);

    setSize(sizeX, sizeY);
    setScale(2);

    // Coordinate object
    auto location = std::make_shared<Course::Coordinate>(0, 0);
    Course::Coordinate& locationref = *location;

    //Aeta::Grassland* grasstile = new Aeta::Grassland(locationref, gameEventHandler_, objectManager_, 1, 1, {});

    // Draw each tile
    int x = 0;
    int y = 0;
    while (x < sizeX) {
        while (y < sizeY){
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

//void drawMap(double scale)





void MapWindow::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> nHandler)
{
    gameEventHandler_ = nHandler;
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

void MapWindow::on_horizontalSlider_valueChanged(int value)
{
    setScale(value);
    generateMap();

}
