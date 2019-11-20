#include "objectmanager.hh"

namespace Aeta {

ObjectManager::ObjectManager() : Course::iObjectManager() {

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase>> &tiles) {

    for (auto item : tiles) {
        tiles_.push_back(item);
    }
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate) {

    for (auto tile : tiles_) {

        if (tile->getCoordinate() == coordinate) {
            return tile;
        }
    }
    return nullptr;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id) {

    for (auto item : tiles_) {

        if (item->ID == id) {
            return item;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Course::TileBase>> ObjectManager::getTiles(
        const std::vector<Course::Coordinate> &coordinates) {

    std::vector<std::shared_ptr<Course::TileBase>> returnvector = {};

    for (auto location : coordinates) {

        for (auto tile : tiles_) {

            if (tile->getCoordinate() == location) {
                returnvector.push_back(tile);
            }
        }
    }
    return returnvector;
}

void ObjectManager::addBuilding(const std::shared_ptr<Course::BuildingBase> &building) {
    buildings_.push_back(building);
}

std::shared_ptr<Course::BuildingBase> ObjectManager::getBuilding(const Course::Coordinate &coordinate) {

    for (auto building : buildings_) {

        if (building->getCoordinate() == coordinate) {
            return building;
        }
    }
    return nullptr;
}

std::shared_ptr<Course::BuildingBase> ObjectManager::getBuilding(const Course::ObjectId &id)
{
    for (auto building : buildings_) {

        if (building->ID == id) {
            return building;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Course::BuildingBase>> ObjectManager::getBuildings(
        const std::vector<Course::Coordinate> &coordinates) {

    std::vector<std::shared_ptr<Course::BuildingBase>> returnvector = {};

    for (auto location : coordinates) {

        for (auto building : buildings_) {

            if (building->getCoordinate() == location) {
                returnvector.push_back(building);
            }
        }
    }
    return returnvector;
}

void ObjectManager::addUnit(const std::shared_ptr<UnitBase> &unit) {
    units_.push_back(unit);
}

std::shared_ptr<UnitBase> ObjectManager::getUnit(const Course::Coordinate &coordinate) {
    for (auto unit : units_) {

        if (unit->getCoordinate() == coordinate) {
            return unit;
        }
    }
    return nullptr;
}

std::shared_ptr<UnitBase> ObjectManager::getUnit(const Course::ObjectId &id) {

    for (auto unit : units_) {

        if (unit->ID == id) {
            return unit;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<UnitBase>> ObjectManager::getUnits(const std::vector<Course::Coordinate> &coordinates) {

    std::vector<std::shared_ptr<UnitBase>> returnvector = {};

    for (auto location : coordinates) {

        for (auto unit : units_) {

            if (unit->getCoordinate() == location) {
                returnvector.push_back(unit);
            }
        }
    }
    return returnvector;
}

std::vector<std::shared_ptr<UnitBase> > ObjectManager::getAllUnits() {

    return units_;

}

} // namespace Aeta
