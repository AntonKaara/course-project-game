#include "objectmanager.hh"

namespace Aeta {

ObjectManager::ObjectManager() : Course::iObjectManager() {

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase>> &tiles) {
    for (auto item : tiles) {
        tilevector_.push_back(item);
    }
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate) {
    for (auto tile : tilevector_) {
        if (tile->getCoordinate() == coordinate) {
            return tile;
        }
    }
    return nullptr;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id) {
    for (auto item : tilevector_) {
        if (item->ID == id) {
            return item;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Course::TileBase>> ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates) {
    std::vector<std::shared_ptr<Course::TileBase>> returnvector = {};
    for (auto location : coordinates) {
        for (auto tile : tilevector_) {
            if (tile->getCoordinate() == location) {
                returnvector.push_back(tile);
            }
        }
    }
    return returnvector;
}

} // namespace Aeta
