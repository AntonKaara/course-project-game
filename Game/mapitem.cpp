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
    QPixmap scaledPixmap = mapItemPictures_.at(tileType);

    std::shared_ptr<Course::BuildingBase> building = nullptr;
    std::string buildingType = "";
    std::shared_ptr<Course::WorkerBase> unit = nullptr;
    std::string unitType = "";

    // Draw building or unit if tile has one
    if (tileObject_->getBuildingCount() > 0) {
        building = tileObject_->getBuildings().at(0);
        buildingType = building->getType();


        // Determine different building pics for both players
        if (tileObject_->getOwner()->getName() == "1") {
            buildingType = buildingType + "1";
        } else {
            buildingType = buildingType + "2";
        }
        scaledPixmap = mapItemPictures_.at(buildingType).scaled(
                    objectSize_, Qt::IgnoreAspectRatio);

    } else if (tileObject_->getWorkerCount() > 0) {
        unit = tileObject_->getWorkers().at(0);
        unitType = unit->getType();

         // Determine different unit pics for both players

        if (tileObject_->getOwner()->getName() == "1") {
            unitType = unitType + "1";
        } else {
            unitType = unitType + "2";
        }

        scaledPixmap = mapItemPictures_.at(unitType).scaled(
                    objectSize_, Qt::IgnoreAspectRatio);

    } else {
        scaledPixmap = mapItemPictures_.at(tileType).scaled(
                    objectSize_, Qt::IgnoreAspectRatio);
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

    std::vector<std::string> types = {"Archer1", "Archer2",
                                      "Coins", "Farm", "Farm1", "Farm2",
                                      "Food", "Forest", "Forest1",
                                      "Forest2", "Grass", "Grass1",
                                      "Grass2", "Headquarters",
                                      "Headquarters1", "Headquarters2",
                                      "Infantry1", "Infantry2", "Ore",
                                      "Outpost", "Outpost1","Outpost2",
                                      "Wood", "Workforce"};

    for (auto mapItemType : types) {
        QString filePath = QString::fromStdString(":/pictures/pictures/"
                                                  + mapItemType + ".png");
        QPixmap image(filePath);
        mapItemPictures_.insert({mapItemType, image});
    }

}

void MapItem::drawTileIndicator() {
    boundingRect().setWidth(4);
    boundingRect().setHeight(4);
    QPainter painter;
    painter.drawRect(boundingRect());
}

} // namespace Aeta


