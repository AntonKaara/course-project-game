#ifndef GRASSTILE_H
#define GRASSTILE_H

#include "tiles/tilebase.h"

#include "player.hh"

#include <string>

namespace Aeta {

/**
 * @brief The GrassTile class represents a grass maptile in the game world
 */
class GrassTile : public Course::TileBase {

public:

    /**
     * @brief Disabled parameterless constructor.
     */
    GrassTile() = delete;

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
    GrassTile(const Course::Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 1,
              const Course::ResourceMap& production =
              Course::ConstResourceMaps::GRASSLAND_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~GrassTile() override = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

};

} // namespace Aeta

#endif // GRASSTILE_H
