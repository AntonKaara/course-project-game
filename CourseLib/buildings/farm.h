#ifndef FARM_H
#define FARM_H

#include "buildingbase.h"


namespace Course {

/**
 * @brief The Farm class represents a farm-building in the game.
 *
 * The farm adds 2 base-production for food.
 */
class Farm : public BuildingBase
{
public:
    static const ResourceMap BUILD_COST;
    static const ResourceMap PRODUCTION_EFFECT;

    /**
     * @brief Disabled default constructor.
     */
    Farm() = delete;

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
    explicit Farm(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<iObjectManager>& objectmanager,
            const std::shared_ptr<PlayerBase>& owner
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Farm() = default;

    /**
     * @copydoc GameObject::getType()
     */
    static std::string getType();

    virtual const ResourceMap getProduction() override;

}; // class Farm

} // namespace Course


#endif // FARM_H
