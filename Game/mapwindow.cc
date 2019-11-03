#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "graphics/simplemapitem.h"
#include "core/resourcemaps.h"
#include "core/worldgenerator.h"

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
    m_simplescene(new Course::SimpleGameScene(this))
{
    ui_->setupUi(this);

    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();

    ui_->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));

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
    worldGen.addConstructor<Course::Grassland>(80);
    worldGen.addConstructor<Course::Forest>(20);
    worldGen.generateMap(sizeX, sizeY, seed, objectManager_, gameEventHandler_);

    setSize(sizeX * 5, sizeY * 5);
    setScale(20);

    // Coordinate object
    auto location = std::make_shared<Course::Coordinate>(0, 0);
    Course::Coordinate& locationref = *location;

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


// Pre-made functions:

void MapWindow::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> nHandler)
{
    gameEventHandler_ = nHandler;
}

void MapWindow::setSize(int width, int height)
{
    m_simplescene->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    m_simplescene->setScale(scale);
}

void MapWindow::resize()
{
    m_simplescene->resize();
}

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->updateItem(obj);
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}
