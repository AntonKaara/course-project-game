#include "interfaces/iobjectmanager.h"
#include "core/gameobject.h"
#include "tiles/tilebase.h"
#include "core/coordinate.h"

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

    // Buildings
    void addBuilding (const std::shared_ptr<Course::BuildingBase> &building);
    std::shared_ptr<Course::BuildingBase> getBuilding (const Course::Coordinate &coordinate);
    std::shared_ptr<Course::BuildingBase> getBuilding (const Course::ObjectId &id);
    std::vector<std::shared_ptr<Course::BuildingBase>> getBuildings (
            const std::vector<Course::Coordinate> &coordinates);

    // Units
    void addUnit (const std::shared_ptr<Course::WorkerBase> &unit);
    std::shared_ptr<Course::WorkerBase> getUnit (const Course::Coordinate &coordinate);
    std::shared_ptr<Course::WorkerBase> getUnit (const Course::ObjectId &id);
    std::vector<std::shared_ptr<Course::WorkerBase>> getUnits (
            const std::vector<Course::Coordinate> &coordinates);

private:

    std::vector<std::shared_ptr<Course::TileBase>> tiles_ = {};
    std::vector<std::shared_ptr<Course::BuildingBase>> buildings_ = {};
    std::vector<std::shared_ptr<Course::WorkerBase>> units_ = {};

};

} // namespace Aeta

#endif // OBJECTMANAGER_HH
