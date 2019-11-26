#ifndef GRASSTILE_H
#define GRASSTILE_H

#include "tiles/tilebase.h"

#include "player.hh"

#include <string>

namespace Aeta {

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
