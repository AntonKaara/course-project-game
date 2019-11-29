#ifndef LAKE_H
#define LAKE_H

#include "tiles/tilebase.h"

namespace Aeta {

/**
 * @brief The Lake class represents lakes in the gameworld.
 *
 * @note can't build on a lake
 */
class Lake : public Course::TileBase {

public:

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the game's GameEventHandler.
     */
    Lake(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 0,
         const unsigned int& max_work = 0,
         const Course::ResourceMap& production = {});

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

};

} // namespace Aeta

#endif // LAKE_H
