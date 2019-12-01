#include "gamescene.h"
#include "mapitem.h"
#include "mapwindow.hh"
#include "gameeventhandler.hh"

#include <QEvent>
#include <QGraphicsItem>

#include <math.h>

namespace Aeta {

GameScene::GameScene(QWidget* parent,
                             int width,
                             int height,
                             int scale):
    QGraphicsScene(parent),
    mapBounds_(nullptr),
    mapWidth_(10),
    mapHeight_(10),
    tileScale_(60) {

    setSize(width, height);
    setScale(scale);

}

void GameScene::setSize(int width, int height) {

    mapWidth_ = width;
    mapHeight_ = height;
    resize();

}

void GameScene::setScale(int scale) {

    tileScale_ = scale;
    resize();

}

void GameScene::resize() {

    // Remove existing map boundary
    if ( mapBounds_ != nullptr ){
        QGraphicsScene::removeItem(mapBounds_);
    }

    QRect rectangle = QRect(0, 0, static_cast<int>(mapWidth_ * tileScale_),
                        static_cast<int>(mapHeight_ * tileScale_));
    addRect(rectangle, QPen(Qt::black));
    setSceneRect(rectangle);
    mapBounds_ = itemAt(rectangle.topLeft(), QTransform());

    // Draw on the bottom of all items
    mapBounds_->setZValue(-1);

}

std::pair<int, int> GameScene::getSize() const {

    return {mapWidth_, mapHeight_};

}

void GameScene::updateItem(std::shared_ptr<Course::GameObject> obj) {

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

void GameScene::removeItem(std::shared_ptr<Course::GameObject> obj) {

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

void GameScene::drawTile(std::shared_ptr<Course::TileBase> tile) {

    MapItem* mapItem = new MapItem(tile, tileScale_);
    addItem(mapItem);

}

void GameScene::drawMoveMarker(std::shared_ptr<Course::TileBase> tile) {

    QGraphicsRectItem* marker = new QGraphicsRectItem(0, 0, 60, 60);

    QPen pen;
    pen.setWidth(1);
    QColor color;
    color.setRgb(0, 0, 0);
    pen.setColor(color);
    marker->setPen(pen);
    marker->setPos(tile->getCoordinate().asQpoint() * 60);
    marker->setOpacity(0.4);
    marker->setBrush(Qt::blue);
    QGraphicsScene::addItem(marker);
    moveMarkers_.push_back(marker);

}

void GameScene::removeMoveMarkers() {

    for (auto item : moveMarkers_) {
        QGraphicsScene::removeItem(item);
    }
    moveMarkers_.clear();

}

void GameScene::drawAttackMarker(std::shared_ptr<Course::TileBase> tile) {

    QGraphicsRectItem* marker = new QGraphicsRectItem(0, 0, 60, 60);

    QPen pen;
    pen.setWidth(1);
    QColor color;
    color.setRgb(0, 0, 0);
    pen.setColor(color);
    marker->setPen(pen);
    marker->setPos(tile->getCoordinate().asQpoint() * 60);
    marker->setOpacity(0.4);
    marker->setBrush(Qt::red);
    QGraphicsScene::addItem(marker);
    attackMarkers_.push_back(marker);

}

void GameScene::removeAttackMarkers() {

    for (auto item : attackMarkers_) {
        QGraphicsScene::removeItem(item);
    }
    attackMarkers_.clear();

}


uint GameScene::tileClicked(QEvent *event, bool moveHighlighter) {

    removeMoveMarkers();
    removeAttackMarkers();

    if (event->type() == QEvent::GraphicsSceneMousePress) {
        QGraphicsSceneMouseEvent* mouseEvent =
                dynamic_cast<QGraphicsSceneMouseEvent*>(event);

        if (sceneRect().contains(mouseEvent->scenePos())) {
            QPointF point = mouseEvent->scenePos();
            point.rx() = floor(point.rx());
            point.ry() = floor(point.ry());

            // Pressed item has to be the tile which is second last item on the items vector
            QGraphicsItem* pressed = items(point).at(items(point).size() - 2);
            MapItem* mapItemPressed = static_cast<MapItem*>(pressed);

            // Move highlightrectangle if needed
            if (moveHighlighter) {
                QGraphicsScene::removeItem(highlightRectangle_);

                // Configure properties for the the indicator rectangle
                QPen pen;
                pen.setWidth(1);
                QColor color;
                color.setRgb(255, 165, 0);
                pen.setColor(color);
                pen.setWidth(4);

                highlightRectangle_ = addRect(mapItemPressed->boundingRect(), pen);

            }

            lastTileId_ = mapItemPressed->getBoundObject()->ID;
            return lastTileId_;
        }
    }
    return 0;
}

} // namespace Aeta
