#include "mapitem.h"

#include <QString>
#include <QPixmap>
#include <math.h>
#include <memory>

namespace Aeta {

MapItem::MapItem(const std::shared_ptr<Course::TileBase> &obj, int size) {

    tileScale_ = size;
    tileObject_ = obj;
    sceneLocation_ = tileObject_->getCoordinatePtr()->asQpoint();

    addMapItemPictures(); // Create map of game objects' pictures

    objectSize_ = mapItemPictures_.at(tileObject_->getType()).size(); // 60x60

}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) {

    Q_UNUSED(option) Q_UNUSED(widget)

    std::string tileType = tileObject_->getType();

    // Location and pixmap texture variable for a tile
    QPointF scaledLocation = sceneLocation_ * tileScale_;
    QPixmap tilePixmap = mapItemPictures_.at(tileType);
    QPixmap unitPixmap = mapItemPictures_.at(tileType);

    std::shared_ptr<Course::BuildingBase> building = nullptr;
    std::string buildingType = "";
    std::shared_ptr<Course::WorkerBase> unit = nullptr;
    std::string unitType = "";

    // Draw building

    if (tileObject_->getBuildingCount() > 0) {

        building = tileObject_->getBuildings().at(0);
        buildingType = building->getType();

        // Determine different building pics for both players
        if (tileObject_->getOwner()->getName() == "1") {
            buildingType = buildingType + "1";
        } else {
            buildingType = buildingType + "2";
        }
        tilePixmap = mapItemPictures_.at(buildingType).scaled(
                    objectSize_, Qt::IgnoreAspectRatio);

    } else {

        if (tileObject_->getOwner() != nullptr) {

            if (tileObject_->getOwner()->getName() == "1") {
                tileType = tileType + "1";
            } else if (tileObject_->getOwner()->getName() == "2") {
                tileType = tileType + "2";
            }
        }

        tilePixmap = mapItemPictures_.at(tileType).scaled(
                    objectSize_, Qt::IgnoreAspectRatio);

    }

    painter->drawPixmap(scaledLocation, tilePixmap);

    // Draw unit

    if (tileObject_->getWorkerCount() > 0) {

        unit = tileObject_->getWorkers().at(0);
        unitType = unit->getType();

       if (unit->getOwner()->getName() == "1") {
           unitType = unitType + "1";
       } else {
           unitType = unitType + "2";
       }

       unitPixmap = mapItemPictures_.at(unitType).scaled(
                    objectSize_, Qt::IgnoreAspectRatio);
       painter->drawPixmap(scaledLocation, unitPixmap);
    }


    painter->drawRect(boundingRect());
    prepareGeometryChange();

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

    std::vector<std::string> types = {"Archery", "Archery1", "Archery2",
                                      "Archery1Free", "Archery1Owned",
                                      "Archery2Free", "Archery2Owned",
                                      "Cavalry", "Cavalry1", "Cavalry2",
                                      "Cavalry1Free",
                                      "Cavalry1Owned", "Cavalry2Free",
                                      "Cavalry2Owned",
                                      "Coins", "Farm", "Farm1", "Farm2",
                                      "Food", "Forest", "Forest1",
                                      "Forest2", "Grass", "Grass1",
                                      "Grass2", "Headquarters",
                                      "Headquarters1", "Headquarters2",
                                      "Infantry", "Infantry1", "Infantry2",
                                      "Infantry1Free", "Infantry1Owned",
                                      "Infantry2Free", "Infantry2Owned",
                                      "Lake", "Lake1", "Lake2",
                                      "Lumbermill", "Lumbermill1",
                                      "Lumbermill2", "Mine", "Mine1",
                                      "Mine2", "Mountain", "Mountain1",
                                      "Mountain2",
                                      "Ore", "Outpost", "Outpost1",
                                      "Outpost2", "Stone", "Swamp", "Swamp1",
                                      "Swamp2", "Wood", "Workforce"};

    for (auto mapItemType : types) {
        QString filePath = QString::fromStdString(":/pictures/pictures/"
                                                  + mapItemType + ".png");
        QPixmap image(filePath);
        mapItemPictures_.insert({mapItemType, image});
    }

}

} // namespace Aeta


