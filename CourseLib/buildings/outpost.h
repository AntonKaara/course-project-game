#ifndef OUTPOST_H
#define OUTPOST_H

#include "buildingbase.h"


namespace Course {

/**
 * @brief The Outpost class represents a player's Outpost-building.
 *
 * It can be constructed on any tile that has not been claimed by any other
 * player. \n
 * Effects: Claims surrounding unclaimed tiles. \n
 * Radius: 2 tiles
 */
class Outpost : public BuildingBase
{
public:
    /**
     * @brief Disabled default constructor.
     */
    Outpost() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param tile points to the tile upon which the building is constructed.
     *
     * @post Exception Guarantee: No guarantee.
     * @exception OwnerConflict - if the building conflicts with tile's
     * ownership.
     */
    explicit Outpost(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<iObjectManager>& objectmanager,
            const std::shared_ptr<PlayerBase>& owner,
            const std::shared_ptr<TileBase>& tile
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Outpost() = default;

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

    /**
     * @brief This building has no action.
     */
    void doAction() override;

}; // class Outpost

} // namespace Course


#endif // OUTPOST_H
