#include "objectmanager.hh"
#include <QDebug>

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

void ObjectManager::removeTile(const std::shared_ptr<Course::TileBase> &tile) {
    uint id = tile.get()->ID;
    auto it = find_if(tiles_.begin(), tiles_.end(), [&id](const std::shared_ptr<Course::TileBase>& tile) {return tile->ID == id;});
    if (it != tiles_.end())
    {
      qDebug() << tiles_.size();
      tiles_.erase(it);
      qDebug() << tiles_.size();
    }
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

void ObjectManager::removeBuilding(const std::shared_ptr<Course::BuildingBase> &building) {

    uint id = building.get()->ID;
    auto it = find_if(buildings_.begin(), buildings_.end(), [&id](const std::shared_ptr<Course::BuildingBase>& building) {return building->ID == id;});
    if (it != buildings_.end())
    {
      qDebug() << buildings_.size();
      buildings_.erase(it);
      qDebug() << buildings_.size();
    }

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

void ObjectManager::removeUnit(const std::shared_ptr<UnitBase> &unit) {

    uint id = unit.get()->ID;
    auto it = find_if(units_.begin(), units_.end(), [&id](const std::shared_ptr<UnitBase>& unit) {return unit->ID == id;});
    if (it != units_.end())
    {
      qDebug() << units_.size();
      units_.erase(it);
      qDebug() << units_.size();
    }

}

} // namespace Aeta
