#include "interfaces/iobjectmanager.h"
#include "core/gameobject.h"
#include "tiles/tilebase.h"
#include "core/coordinate.h"
#include "unitbase.h"

#include <memory>
#include <vector>

#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

namespace Aeta {

class ObjectManager : public Course::iObjectManager {

public:

    ObjectManager();
    ~ObjectManager() = default;

    // Tiles
    void addTiles (const std::vector<std::shared_ptr<Course::TileBase>> &tiles);
    std::shared_ptr<Course::TileBase> getTile (const Course::Coordinate &coordinate);
    std::shared_ptr<Course::TileBase> getTile (const Course::ObjectId &id);
    std::vector<std::shared_ptr<Course::TileBase>> getTiles (
            const std::vector<Course::Coordinate> &coordinates);
    void removeTile (const std::shared_ptr<Course::TileBase> &tile);

    // Buildings
    void addBuilding (const std::shared_ptr<Course::BuildingBase> &building);
    std::shared_ptr<Course::BuildingBase> getBuilding (const Course::Coordinate &coordinate);
    std::shared_ptr<Course::BuildingBase> getBuilding (const Course::ObjectId &id);
    std::vector<std::shared_ptr<Course::BuildingBase>> getBuildings (
            const std::vector<Course::Coordinate> &coordinates);
    void removeBuilding (const std::shared_ptr<Course::BuildingBase> &building);

    // Units
    void addUnit (const std::shared_ptr<UnitBase> &unit);
    std::shared_ptr<UnitBase> getUnit (const Course::Coordinate &coordinate);
    std::shared_ptr<UnitBase> getUnit (const Course::ObjectId &id);
    std::vector<std::shared_ptr<UnitBase>> getUnits (
            const std::vector<Course::Coordinate> &coordinates);
    std::vector<std::shared_ptr<UnitBase>> getAllUnits();
    void removeUnit (const std::shared_ptr<UnitBase> &unit);

private:

    std::vector<std::shared_ptr<Course::TileBase>> tiles_ = {};
    std::vector<std::shared_ptr<Course::BuildingBase>> buildings_ = {};
    std::vector<std::shared_ptr<UnitBase>> units_ = {};

};

} // namespace Aeta

#endif // OBJECTMANAGER_HH
