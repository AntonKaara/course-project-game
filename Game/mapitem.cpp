#include "mapitem.h"
#include <QString>
#include <QPixmap>
#include <math.h>

namespace Aeta {

MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj,
                 int size) {

    tileScale_ = size;
    gameObject_ = obj;
    sceneLocation_ = gameObject_->getCoordinatePtr()->asQpoint();

    addMapItemPictures();

    // 60x60
    objectSize_ = mapItemPictures_.at(gameObject_->getType()).size();



}

QRectF MapItem::boundingRect() const {

    return QRectF(sceneLocation_ * tileScale_, objectSize_);

}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) {

    Q_UNUSED(option) Q_UNUSED(widget)


    QPointF scaledLocation = sceneLocation_ * tileScale_;
    QPixmap scaledPixmap = mapItemPictures_.at(
                gameObject_->getType()).scaled(objectSize_, Qt::IgnoreAspectRatio);
    painter->drawPixmap(scaledLocation, scaledPixmap);
    painter->drawRect(boundingRect());

}


const std::shared_ptr<Course::GameObject> &MapItem::getBoundObject() {

    return gameObject_;

}

void MapItem::updateLoc() {

    if ( !gameObject_ ){
        delete this;
    } else {
        update(boundingRect()); // Test if necessary
        sceneLocation_ = gameObject_->getCoordinate().asQpoint();
    }

}

bool MapItem::isSameObj(std::shared_ptr<Course::GameObject> obj) {

    return obj == gameObject_;

}

int MapItem::getSize() const {

    return tileScale_;

}

void MapItem::setSize(int size) {

    tileScale_ = size;

}

void MapItem::addMapItemPictures() {

    std::vector<std::string> types = {"archer", "foresttile", "grasstile", "headquarters", "infantry", "outpostPlayer1", "outpostPlayer2", "farm"};

    for (auto mapItemType : types) {
        QString filePath = QString::fromStdString(":/pictures/pictures/"
                                                  + mapItemType + ".png");
        QPixmap image(filePath);
        mapItemPictures_.insert({mapItemType, image});
    }

}

} // namespace Aeta


