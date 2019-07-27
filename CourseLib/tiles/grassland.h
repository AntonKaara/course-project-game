#ifndef GRASSLAND_H
#define GRASSLAND_H

#include "tilebase.h"


namespace Course {

/**
 * @brief The Grassland class represents Grassland in the gameworld.
 *
 * Grassland has BasicProduction: \n
 * Money = 1 \n
 * Food = 2 \n
 * Wood = 1 \n
 * Stone = 0 \n
 * Ore = 0 \n
 *
 * Functionality follows mainly the parent class' functionality.
 *
 * Tile supports 3 buildings.
 *
 * @invariant Weak-pointer to GameEventHandler hasn't expired.
 */
class Grassland : public TileBase
{
public:
    /**
     * @brief Disabled default constructor.
     */
    Grassland() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Grassland(const Coordinate& location,
              const std::shared_ptr<iGameEventHandler>& eventhandler,
              const std::shared_ptr<iObjectManager>& objectmanager);

    /**
     * @brief Default destructor.
     */
    virtual ~Grassland() = default;

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

}; // class Grassland

} // namespace Course


#endif // GRASSLAND_H
