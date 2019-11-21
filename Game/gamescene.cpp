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

int GameScene::getScale() const {

    return tileScale_;

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

void GameScene::drawTile(std::shared_ptr<Course::TileBase> obj) {

    MapItem* mapItem = new MapItem(obj, tileScale_);
    addItem(mapItem);

}


uint GameScene::tileClicked(QEvent *event, bool moveHighlighter) {

    if (event->type() == QEvent::GraphicsSceneMousePress) {
        QGraphicsSceneMouseEvent* mouseEvent =
                dynamic_cast<QGraphicsSceneMouseEvent*>(event);

        if (sceneRect().contains(mouseEvent->scenePos())) {
            QPointF point = mouseEvent->scenePos();
            QGraphicsItem* pressed = itemAt(point, QTransform());
            MapItem* mapItemPressed = static_cast<MapItem*>(pressed);



            // Move highlightrectangle if needed
            if (moveHighlighter) {

                // Configure properties for the the indicator rectangle
                QPen pen;
                pen.setWidth(1);
                QColor color;
                color.setRgb(255, 165, 0);
                pen.setColor(color);
                pen.setWidth(4);

                /* If there is a highlighted tile already remove the effect.
                 * Don't add anything if the clicked tile is already highlighted.
                 *
                 */

                if (highlightRectangle_ != nullptr) {

                    if (highlightRectangle_->boundingRect() == mapItemPressed->boundingRect()) {
                        return lastTileId_;
                    } else {

                        QGraphicsScene::removeItem(highlightRectangle_);

                    }

                }

                highlightRectangle_ = addRect(mapItemPressed->boundingRect(), pen);

            }
            lastTileId_ = mapItemPressed->getBoundObject()->ID;
            return lastTileId_;
        }
    }
    return 0;
}

} // namespace Aeta
