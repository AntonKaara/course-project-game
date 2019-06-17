#ifndef FARM_H
#define FARM_H

#include "buildingbase.h"

namespace Course {

/**
 * @brief The Farm class represents a farm-building in the game.
 *
 * The farm adds 2 base-production for food. \n
 *
 */
class Farm : public BuildingBase
{
public:
    /**
     * @brief Default constructor is disabled.
     */
    Farm() = delete;

    /**
     * @brief Constructor for the class
     *
     * @param eventhandler is a weak-pointer to the student's GameEventHandler
     * @param owner is a weak-pointer to the owning player
     *
     * @post Exception Guarantee: No guarantee.
     * @exception OwnerConflict - if the building conflicts with target_tile's
     * ownership.
     */
    explicit Farm(const std::shared_ptr<iGameEventHandler>& eventhandler,
                  const std::shared_ptr<BGBase::PlayerBase>& owner,
                  const std::shared_ptr<TileBase>& tile
                  );


    virtual ~Farm();

    /**
     * @brief This building has no action.
     */
    virtual void doAction() override;

    /**
     * @brief Returns the building's multiplier for the requested resource.
     * @param resource is the resource type production that the building is
     * enhancing.
     * @return The multiplier-value
     */
    virtual double getMultiplier(BasicResource resource) const override;

    /**
     * @brief Return the building's multiplier for the requested resource.
     * @param resource is the resource type that the building is producing.
     * @return The base-production bonus.
     */
    virtual int getProduction(BasicResource resource) const override;

private:


};

}
#endif // FARM_H
