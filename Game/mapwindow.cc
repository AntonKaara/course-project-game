#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "graphics/simplemapitem.h"
#include "gameeventhandler.hh"
#include "tiles/grassland.h"
#include "objectmanager.hh"
#include "core/resourcemaps.h"
#include "core/worldgenerator.h"

#include <memory>
#include <math.h>
#include <iostream>

MapWindow::MapWindow(QWidget *parent):
    //std::shared_ptr<Aeta::GameEventHandler> handler,
    //std::shared_ptr<Aeta::ObjectManager> objectManager
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    //m_GEHandler(handler),
    //m_objectManager(objectManager),
    m_simplescene(new Course::SimpleGameScene(this))
{
    m_ui->setupUi(this);

    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));

    auto gameEventHandler = std::make_shared<Aeta::GameEventHandler>();
    auto objectManager = std::make_shared<Aeta::ObjectManager>();
    m_GEHandler = gameEventHandler;
    m_objectManager = objectManager;

    generateMap();

}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::generateMap()
{
    int sizeX = 20;
    int sizeY = 20;
    int seed = 12345;
//    auto location = std::make_shared<Course::Coordinate>(1, 1);
//    Course::Coordinate& locationref = *location;

    //auto grassland = std::make_shared<Course::Grassland>(
                //locationref, m_GEHandler, m_objectManager);


    Course::WorldGenerator& worldGen = worldGen.getInstance();

    worldGen.addConstructor<Course::Grassland>(100);
    worldGen.generateMap(sizeX, sizeY, seed, m_objectManager, m_GEHandler);

    setSize(sizeX * 4, sizeY * 4);
    setScale(25);
    //resize();
    //drawItem(grassland);


    auto location = std::make_shared<Course::Coordinate>(0, 0);
    Course::Coordinate& locationref = *location;

    int x = 0;
    int y = 0;
    while (x < sizeX) {
        while (y < sizeY){
            auto tile = m_objectManager->getTile(locationref);
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






void MapWindow::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> nHandler)
{
    m_GEHandler = nHandler;
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
