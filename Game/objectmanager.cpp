#include "objectmanager.hh"

namespace Aeta {
ObjectManager::ObjectManager()
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase>> &tiles)
{
    for (auto item : tiles) {
        tilevector_.push_back(item);
    }
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate)
{
    for (auto item : tilevector_) {
        if (item->getCoordinate == coordinate) {
            return item;
        }
    }
    return nullptr; // onkohan järkevää :D?
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    for (auto item : tilevector_) {
        if (item->ID == coordinate) { // mitäh??
            return item;
        }
    }
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    std::vector<std::shared_ptr<Course::TileBase>> returnvector = {};
    for (auto location : coordinates) {
        for (auto tile : tilevector_) {
            if (tile->getCoordinate == location) {
                returnvector.push_back(tile);
            }
        }
    }
    return returnvector;
}

} // namespace Aeta
