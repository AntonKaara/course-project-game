#ifndef BUILDINGBASE_H
#define BUILDINGBASE_H

#include "../placeablegameobject.h"

namespace Course {

class TileBase;

/**
 * @brief The BuildingBase class is an base-class for
 * different building-objects in the game.
 *
 * * Can increase production multiplier for a Tile.
 * * Can increase base-production for a Tile.
 * * Can call functions from GameEventHandler.
 *
 * Buildings can have hold-markers that can prevent normal operation.
 */
class BuildingBase : public PlaceableGameObject
{
public:
    /**
     * @brief Default constructor is disabled.
     */
    BuildingBase() = delete;

    /**
     * @brief Constructor for the class
     *
     * @param eventhandler is a weak-pointer to the student's GameEventHandler
     * @param owner is a weak-pointer to the owning player
     * @param descriptions is map of strings referring to strings.
     *
     * @post Exception Guarantee: No guarantee.
     * @exception OwnerConflict - if the building conflicts with target_tile's
     * ownership.
     */
    explicit BuildingBase(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<BGBase::PlayerBase>& owner,
            const BGBase::Description_map& descriptions = {},
            const std::shared_ptr<TileBase>& tile = {},
            const int& hold = 0
            );

    /**
     * @brief Default destructor.
     */
    virtual ~BuildingBase() = default;

    /**
     * @brief Performs building's default action.
     */
    virtual void doAction();

    /**
     * @brief Returns the building's multiplier for the requested resource.
     * @param resource is the resource type production that the building is
     * enhancing.
     * @return The multiplier-value
     */
    virtual double getMultiplier(BasicResource resource) const;

    /**
     * @brief Return the building's multiplier for the requested resource.
     * @param resource is the resource type that the building is producing.
     * @return The base-production bonus.
     */
    virtual int getProduction(BasicResource resource) const;

    /**
     * @copydoc BGBase::GameObject::getType()
     */
    virtual std::string getType() const;

    /**
     * @brief Adds the amount to HoldMarkers.
     * @note Negative amounts can be used for substraction.
     * @param amount the amount being added.
     * @post Exception guarantee: No-throw
     */
    virtual void addHoldMarkers(int amount) final;

    /**
     * @brief Returns the amount of HoldMarkers.
     * @return value in m_hold.
     * @post Exception guarantee: No-throw
     */
    virtual int holdCount() final;

private:
    int m_hold;
};
}

#endif // BUILDINGBASE_H
