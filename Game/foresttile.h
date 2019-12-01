#ifndef FORESTTILE_H
#define FORESTTILE_H

#include "tiles/tilebase.h"

#include "objectmanager.hh"

#include <string>


namespace Aeta {

/**
 * @brief The ForestTile class represents a forest tile in the game world
 */
class ForestTile : public Course::TileBase
{
public:

    /**
     * @brief Disabled default constructor
     */
    ForestTile() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     * @param objectmanager points to the games's ObjectManager
     * @param max_build The amount of buildings that fit on the tile (not used)
     * @param max_work The amount of units that fit on the tile (not used)
     * @param production has the production per turn listed as a resourcemap.

     */
    ForestTile(const Course::Coordinate& location,
               const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
               const std::shared_ptr<Course::iObjectManager>& objectmanager,
               const unsigned int& max_build = 1,
               const unsigned int& max_work = 1,
               const Course::ResourceMap& production =
               Course::ConstResourceMaps::FOREST_BP);

    /**
     * @brief Default destructor
     */
    virtual ~ForestTile() override = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

};

} // namespace Aeta

#endif // FORESTTILE_H
