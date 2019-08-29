#ifndef HEADQUARTERS_H
#define HEADQUARTERS_H

#include "buildingbase.h"


namespace Course {

/**
 * @brief The HeadQuarters class represents a player's HeadQuarters-building.
 *
 * It can be constructed on any tile that has not been claimed by any other
 * player. \n
 * Effects: Claims surrounding unclaimed tiles. \n
 * Radius: 3 tiles.
 */
class HeadQuarters : public BuildingBase
{
public:
    /**
     * @brief Disabled default constructor.
     */
    HeadQuarters() = delete;

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
    explicit HeadQuarters(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<iObjectManager>& objectmanager,
            const std::shared_ptr<PlayerBase>& owner
            );

    /**
     * @brief Default destructor.
     */
    virtual ~HeadQuarters() = default;

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

    /**
     * @brief Set's 3 neighbouring Tiles' ownership to this building's
     * ownership if the Tiles don't already have an owner.
     */
    void buildAction() override;

}; // class HeadQuarters

} // namespace Course


#endif // HEADQUARTERS_H
