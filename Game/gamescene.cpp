#include "gamescene.h"
#include "mapitem.h"
#include "mapwindow.hh"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include <math.h>

namespace Aeta {

GameScene::GameScene(QWidget* parent,
                             int width,
                             int height,
                             double scale):
    QGraphicsScene(parent),
    mapBounds_(nullptr),
    mapWidth_(10),
    mapHeight_(10),
    mapScale_(60)
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

void GameScene::setScale(double scale)
{
    mapScale_ = scale;
    resize();
}

void GameScene::resize()
{
    if ( mapBounds_ != nullptr ){
        QGraphicsScene::removeItem(mapBounds_);
    }

    QRect rectangle = QRect(0, 0, static_cast<int>(mapWidth_ * mapScale_),
                        static_cast<int>(mapHeight_ * mapScale_));

    addRect(rectangle, QPen(Qt::black));
    setSceneRect(rectangle);
    mapBounds_ = itemAt(rectangle.topLeft(), QTransform());
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

//void GameScene::updateItem(std::shared_ptr<Course::GameObject> obj)
//{
//    QList<QGraphicsItem*> items_list = items();
//    if ( items_list.size() == 1 ){
//        qDebug() << "Nothing to update.";
//    } else {
//        for ( auto item : items_list ){
//            MapItem* mapItem = static_cast<MapItem*>(item);
//            if (mapItem->isSameObj(obj)){
//                mapItem->updateLoc();
//            }
//        }
//    }
//}


//void GameScene::removeItem(std::shared_ptr<Course::GameObject> obj)
//{
//    QList<QGraphicsItem*> items_list = items(obj->getCoordinate().asQpoint());
//    if ( items_list.size() == 1 ){
//        qDebug() << "Nothing to be removed at the location pointed by given obj.";
//    } else {
//        for ( auto item : items_list ){
//            MapItem* mapitem = static_cast<MapItem*>(item);
//            if ( mapitem->isSameObj(obj) ){
//                delete mapitem;
//            }
//        }
//    }
//}

void GameScene::drawItem(std::shared_ptr<Course::GameObject> obj)
{
    MapItem* mapItem = new MapItem(obj, mapScale_);
    addItem(mapItem);
}

//bool GameScene::event(QEvent *event)
//{
//    if(event->type() == QEvent::GraphicsSceneMousePress)
//    {
//        QGraphicsSceneMouseEvent* mouse_event =
//                dynamic_cast<QGraphicsSceneMouseEvent*>(event);

//        if ( sceneRect().contains(mouse_event->scenePos())){

//            QPointF point = mouse_event->scenePos() / mapScale_;

//            point.rx() = floor(point.rx());
//            point.ry() = floor(point.ry());

//            QGraphicsItem* pressed = itemAt(point * mapScale_, QTransform());

//            if ( pressed == mapBounds_ ){
//                qDebug() << "Click on map area.";
//            }else{
//                qDebug() << "ObjID: " <<
//                            static_cast<MapItem*>(pressed)
//                            ->getBoundObject()->ID  << " pressed.";
//                return true;
//            }
//        }
//    }

//    if (event->type() == QEvent::GraphicsSceneWheel) {
//        QGraphicsSceneWheelEvent* mouseWheelEvent =
//                dynamic_cast<QGraphicsSceneWheelEvent*>(event);

//        if (sceneRect().contains(mouseWheelEvent->scenePos())) {
//            mouseWheelEventHandler(mouseWheelEvent);
//            event->accept();
//            return true;
//        }

//    }
//    return false;
//}

} // namespace Aeta
