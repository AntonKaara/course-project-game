#ifndef FOREST_H
#define FOREST_H

#include "tilebase.h"


namespace Course {

/**
 * @brief The Forest class represents Forest in the gameworld.
 *
 * Forest has BasicProduction: \n
 * Money = 1 \n
 * Food = 2 \n
 * Wood = 3 \n
 * Stone = 0 \n
 * Ore = 0 \n
 *
 * Building in the forest takes time. So buildings don't generate resources or
 * bonuses on the first resource generation turn.
 * Clearing space for the building Generates 3 extra wood that turn.
 * Forest loses 1 Wood output for each building.
 *
 * Tile supports 3 buildings.
 */
class Forest : public TileBase
{
public:
    /**
     * @brief Disabled default constructor.
     */
    Forest() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Forest(const Coordinate& location,
           const std::shared_ptr<iGameEventHandler>& eventhandler,
           const std::shared_ptr<iObjectManager>& objectmanager);

    /**
     * @brief Default destructor.
     */
    virtual ~Forest() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Adds a new building-object to the tile.
     *
     * Phases: \n
     * 1. Check that there is space for the building. \n
     * 2. Call parent's addBuilding \n
     * 3. Add a HoldMarker for the building. \n
     *
     * @post Exception guarantee: Strong
     * @exception OwnerConflict - If the tile's ownership prevents placing the
     * \b building.
     * @exception NoSpace - If the tile doesn't have enough space for
     * the \b building.
     */
    void addBuilding(const std::shared_ptr<BuildingBase>& building) override;

}; // class Forest

} // namespace Course


#endif // FOREST_H
