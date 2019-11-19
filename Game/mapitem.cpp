#include "mapitem.h"

#include <QString>
#include <QPixmap>
#include <math.h>
#include <memory>

namespace Aeta {

MapItem::MapItem(const std::shared_ptr<Course::TileBase> &obj,
                 int size) {

    tileScale_ = size;
    tileObject_ = obj;
    sceneLocation_ = tileObject_->getCoordinatePtr()->asQpoint();

    addMapItemPictures(); // Create map of pixmaps

    objectSize_ = mapItemPictures_.at(tileObject_->getType()).size(); // 60x60

}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) {

    Q_UNUSED(option) Q_UNUSED(widget)

    // Changed later if tile has a building
    std::shared_ptr<Course::BuildingBase> building = nullptr;
    std::string buildingType = "No buildings";

    std::string tileType = tileObject_->getType();

    // Location and pixmap texture variable for a tile
    QPointF scaledLocation = sceneLocation_ * tileScale_;
    QPixmap scaledPixmap = mapItemPictures_.at(tileType);

    //tileObject_->getOwner(); // Get player

    // Draw building if tile has buildings
    if (tileObject_->getBuildingCount() > 0) {
        building = tileObject_->getBuildings().at(0);
        buildingType = building->getType();
        scaledPixmap = mapItemPictures_.at(buildingType).scaled(objectSize_, Qt::IgnoreAspectRatio);

        // TODO: Draw different tiles for both players
        if (tileObject_->getOwner()) {

        }

    } else {
        scaledPixmap = mapItemPictures_.at(tileType).scaled(objectSize_, Qt::IgnoreAspectRatio);
    }

    painter->drawPixmap(scaledLocation, scaledPixmap);
    painter->drawRect(boundingRect());

}

QRectF MapItem::boundingRect() const {

    return QRectF(sceneLocation_ * tileScale_, objectSize_);

}

const std::shared_ptr<Course::TileBase> &MapItem::getBoundObject() {

    return tileObject_;

}

void MapItem::updateLoc() {

    if ( !tileObject_ ){
        delete this;
    } else {
        update(boundingRect()); // Test if necessary
        sceneLocation_ = tileObject_->getCoordinate().asQpoint();
    }

}

bool MapItem::isSameObj(std::shared_ptr<Course::GameObject> obj) {

    return obj == tileObject_;

}

int MapItem::getSize() const {

    return tileScale_;

}

void MapItem::setSize(int size) {

    tileScale_ = size;

}

void MapItem::addMapItemPictures() {

    std::vector<std::string> types = {"ArcherPlayer1", "ArcherPlayer2",
                                      "Coins", "Farm", "FarmPlayer2",
                                      "Food", "Forest", "ForestPlayer1",
                                      "ForestPlayer2", "Grass",
                                      "Headquarters",
                                      "HeadquartersPlayer2", "InfantryPlayer1",
                                      "InfantryPlayer2", "Ore",
                                      "Outpost", "OutpostPlayer2",
                                      "Player1OwnedGrass", "Player2OwnedGrass",
                                      "Wood", "Workforce"};

    for (auto mapItemType : types) {
        QString filePath = QString::fromStdString(":/pictures/pictures/"
                                                  + mapItemType + ".png");
        QPixmap image(filePath);
        mapItemPictures_.insert({mapItemType, image});
    }

}

void MapItem::drawSelectedIndicator() {
    boundingRect().setWidth(4);
    boundingRect().setHeight(4);
    QPainter painter;
    painter.drawRect(boundingRect());
}

} // namespace Aeta


