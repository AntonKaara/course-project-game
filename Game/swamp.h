#ifndef SWAMP_H
#define SWAMP_H

#include "tiles/tilebase.h"

namespace Aeta {

/**
 * @brief Swamp class represents a swamp in the gameworld.
 */
class Swamp : public Course::TileBase {

public:

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     * @param objectmanager points to the games's ObjectManager
     * @param max_build The amount of buildings that fit on the tile (not used)
     * @param max_work The amount of units that fit on the tile (not used)
     * @param production has the production per turn listed as a resourcemap = nothing
     *
     */
    Swamp(const Course::Coordinate& location,
          const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
          const std::shared_ptr<Course::iObjectManager>& objectmanager,
          const unsigned int& max_build = 1,
          const unsigned int& max_work = 1,
          const Course::ResourceMap& production = {});

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

};

} // namespace Aeta

#endif // SWAMP_H
