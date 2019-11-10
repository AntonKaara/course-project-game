#include "mapitem.h"
#include <QString>
#include <QPixmap>

namespace Aeta {

std::map<std::string, QPixmap> MapItem::mapItemPictures_ = {};

MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj) {

    gameObject_ = obj;
    sceneLocation_ = gameObject_->getCoordinatePtr()->asQpoint();

    // add the picture representing gameObject_ to the mapItemPictures

    addMapItemPicture(gameObject_->getType());

    objectSize_ = mapItemPictures_.at(gameObject_->getType()).size();

}

// dunno if needed
//QRectF MapItem::boundingRect() const {
//    return QRectF(sceneLocation_, objectSize_);
//}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) {

    Q_UNUSED(option) Q_UNUSED(widget)

    painter->drawPixmap(sceneLocation_, mapItemPictures_.at(gameObject_->getType()));

}

void MapItem::addMapItemPicture(std::string mapItemType) {

    // generate QImage-object with the right picture

    QString filePath = QString::fromStdString(":/pictures/pictures/" +
                                              mapItemType + ".png");
    QPixmap objectImage(filePath);
    mapItemPictures_.insert({mapItemType, objectImage});

}
} // namespace Aeta


