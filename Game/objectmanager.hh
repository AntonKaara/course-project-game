#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

#include "interfaces/iobjectmanager.h"
#include "core/gameobject.h"
#include "core/coordinate.h"
#include "tiles/tilebase.h"

#include "unitbase.h"

#include <memory>
#include <vector>

namespace Aeta {

/**
 * @brief The ObjectManager class stores and keeps track of gameObjects.
 */
class ObjectManager : public Course::iObjectManager {

public:

    /**
     * @brief Class constructor
     */
    ObjectManager();

    /**
     * @brief Default destructor
     */
    ~ObjectManager() = default;


    // Tiles


    /**
     * @brief Stores given tileobjects
     */
    void addTiles (const std::vector<std::shared_ptr<Course::TileBase>> &tiles);

    /**
     * @brief Fetches a tileobject from given coordinate
     * @return TileBase object
     */
    std::shared_ptr<Course::TileBase> getTile (const Course::Coordinate &coordinate);

    /**
     * @brief Fetches a tileobject with given id
     * @return TileBase object
     */
    std::shared_ptr<Course::TileBase> getTile (const Course::ObjectId &id);

    /**
     * @brief Fetches tileobjects from given coordinates
     * @return TileBase object vector
     */
    std::vector<std::shared_ptr<Course::TileBase>> getTiles (
            const std::vector<Course::Coordinate> &coordinates);

    /**
     * @brief Fetches all tileobjects
     * @return TileBase object vector
     */
    std::vector<std::shared_ptr<Course::TileBase>> getAllTiles();

    /**
     * @brief Removes a given tileobject
     */
    void removeTile (const std::shared_ptr<Course::TileBase> &tile);


    // Buildings


    /**
     * @brief Stores a given building
     */
    void addBuilding (const std::shared_ptr<Course::BuildingBase> &building);

    /**
     * @brief Fetches a building from given coordinate
     * @return BuildingBase object
     */
    std::shared_ptr<Course::BuildingBase> getBuilding (const Course::Coordinate &coordinate);

    /**
     * @brief Fetches a building with given id
     * @return BuildingBase object
     */
    std::shared_ptr<Course::BuildingBase> getBuilding (const Course::ObjectId &id);

    /**
     * @brief Fetches buildings from given coordinates
     * @return BuildingBase object vector
     */
    std::vector<std::shared_ptr<Course::BuildingBase>> getBuildings (
            const std::vector<Course::Coordinate> &coordinates);

    /**
     * @brief Fetches all buildings
     * @return BuildingBase object vector
     */
    std::vector<std::shared_ptr<Course::BuildingBase>> getAllBuildings();

    /**
     * @brief Removes a given building
     */
    void removeBuilding (const std::shared_ptr<Course::BuildingBase> &building);


    // Units


    /**
     * @brief Adds given UnitBase object
     * @param Unit to be added
     */
    void addUnit (const std::shared_ptr<UnitBase> &unit);

    /**
     * @brief Fetches unit from given coordinate
     * @return UnitBase object
     */
    std::shared_ptr<UnitBase> getUnit (const Course::Coordinate &coordinate);

    /**
     * @brief Fetches unit with given id
     * @return UnitBase object
     */
    std::shared_ptr<UnitBase> getUnit (const Course::ObjectId &id);

    /**
     * @brief Fetches units from given coordinates
     * @return UnitBase object vector
     */
    std::vector<std::shared_ptr<UnitBase>> getUnits (
            const std::vector<Course::Coordinate> &coordinates);

    /**
     * @brief Fetches all units
     * @return UnitBase object vector
     */
    std::vector<std::shared_ptr<UnitBase>> getAllUnits();

    /**
     * @brief Removes given unit object
     */
    void removeUnit (const std::shared_ptr<UnitBase> &unit);

private:

    std::vector<std::shared_ptr<Course::TileBase>> tiles_ = {};
    std::vector<std::shared_ptr<Course::BuildingBase>> buildings_ = {};
    std::vector<std::shared_ptr<UnitBase>> units_ = {};

};

} // namespace Aeta

#endif // OBJECTMANAGER_HH
