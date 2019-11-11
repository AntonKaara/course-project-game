#include "gamescene.h"
#include "mapitem.h"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include <math.h>

namespace Aeta {

GameScene::GameScene(QWidget* parent,
                             int width,
                             int height,
                             int scale):
    QGraphicsScene(parent),
    mapBounds_(nullptr),
    mapWidth_(20),
    mapHeight_(20),
    mapScale_(80)
{
    setSize(width, height);
    setScale(scale);
}

void GameScene::setSize(int width, int height)
{
    mapWidth_ = width;
    mapHeight_ = height;
    resize();
}

void GameScene::setScale(int scale)
{
    mapScale_ = scale;
    resize();
}

void GameScene::resize()
{
    if ( mapBounds_ != nullptr ){
        QGraphicsScene::removeItem(mapBounds_);
    }

    // Calculates rect with middle at (0,0).
    // Basically left upper corner coords and then width and height
    QRect rect = QRect( 0, 0, mapWidth_ * mapScale_, mapHeight_ * mapScale_);

    addRect(rect, QPen(Qt::black));
    setSceneRect(rect);
    mapBounds_ = itemAt(rect.topLeft(), QTransform());
    // Draw on the bottom of all items
    mapBounds_->setZValue(-1);
}

std::pair<int, int> GameScene::getSize() const
{
    return {mapWidth_, mapHeight_};
}

int GameScene::getScale() const
{
    return mapScale_;
}

void GameScene::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items();
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to update.";
    } else {
        for ( auto item : items_list ){
            MapItem* mapItem = static_cast<MapItem*>(item);
            if (mapItem->isSameObj(obj)){
                mapItem->updateLoc();
            }
        }
    }
}


void GameScene::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items(obj->getCoordinate().asQpoint());
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to be removed at the location pointed by given obj.";
    } else {
        for ( auto item : items_list ){
            MapItem* mapitem = static_cast<MapItem*>(item);
            if ( mapitem->isSameObj(obj) ){
                delete mapitem;
            }
        }
    }
}

void GameScene::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    MapItem* mapItem = new MapItem(obj, mapScale_);
    addItem(mapItem);
}

} // namespace Aeta
