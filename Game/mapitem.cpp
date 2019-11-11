#include "mapitem.h"
#include <QString>
#include <QPixmap>
#include <math.h>

namespace Aeta {

std::map<std::string, QPixmap> MapItem::mapItemPictures_ = {};

MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj, double size) {

    mapScale_ = size;
    gameObject_ = obj;
    sceneLocation_ = gameObject_->getCoordinatePtr()->asQpoint();

    // Add the picture representing gameObject_ to mapItemPictures
    addMapItemPicture(gameObject_->getType());

    // 60x60
    objectSize_ = mapItemPictures_.at(gameObject_->getType()).size();
    pixelScaler_ = objectSize_.width(); // 60

}

QRectF MapItem::boundingRect() const {
    return QRectF(sceneLocation_ * mapScale_ * pixelScaler_, objectSize_ * mapScale_);
}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) {

    Q_UNUSED(option) Q_UNUSED(widget)


    QPointF scaledLocation = sceneLocation_ * mapScale_ * pixelScaler_;
    QPixmap scaledPixmap = mapItemPictures_.at(
                gameObject_->getType()).scaled(objectSize_ * mapScale_, Qt::IgnoreAspectRatio);
    painter->drawPixmap(scaledLocation, scaledPixmap);
    painter->drawRect(boundingRect());

}

void MapItem::addMapItemPicture(std::string mapItemType) {

    // generate QImage-object with the right picture

    QString filePath = QString::fromStdString(":/pictures/pictures/" +
                                              mapItemType + ".png");
    QPixmap objectImage(filePath);
    mapItemPictures_.insert({mapItemType, objectImage});

}
} // namespace Aeta


