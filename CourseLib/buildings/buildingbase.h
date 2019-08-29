#ifndef BUILDINGBASE_H
#define BUILDINGBASE_H

#include "core/placeablegameobject.h"
#include "core/basicresources.h"


namespace Course {

class TileBase;

/**
 * @brief The BuildingBase class is a base-class for
 * different buildings in the game.
 *
 * * Can increase production multiplier for a Tile.
 * * Can increase base-production for a Tile.
 * * Can call functions from GameEventHandler.
 *
 * Buildings can have hold-markers that prevent normal operation.
 */
class BuildingBase : public PlaceableGameObject
{
public:
    /**
     * @brief Disabled default constructor.
     */
    BuildingBase() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param descriptions contains descriptions and flavor texts.
     * @param tile points to the tile upon which the building is constructed.
     * @param hold is the initial amount of hold-markers.
     *
     * @post Exception Guarantee: No guarantee.
     * @exception OwnerConflict - if the building conflicts with tile's
     * ownership.
     */
    explicit BuildingBase(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<iObjectManager>& objectmanager,
            const std::shared_ptr<PlayerBase>& owner,
            const int& tilespaces = 1,
            const int& hold = 0
            );

    /**
     * @brief Default destructor.
     */
    virtual ~BuildingBase() = default;

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

    /**
     * @brief Performs building's default action.
     */
    virtual void doAction();

    /**
     * @brief Performs building's possible action after construction.
     */
    virtual void buildAction();

    /**
     * @brief Returns the building's multiplier for the requested resource.
     * @param resource is the resource type whose production the building is
     * enhancing.
     * @return The multiplier-value.
     */
    virtual double getMultiplier(BasicResource resource) const;

    /**
     * @brief Return the building's multiplier for the requested resource.
     * @param resource is the resource type that the building is producing.
     * @return The base-production bonus.
     */
    virtual int getProduction(BasicResource resource) const;

    /**
     * @brief Adds the amount to hold-markers.
     * @note Negative amounts can be used for substraction.
     * @param amount the amount being added.
     * @post Exception guarantee: No-throw
     */
    virtual void addHoldMarkers(int amount) final;

    /**
     * @brief Returns the amount of hold-markers.
     * @return value in m_hold.
     * @post Exception guarantee: No-throw
     */
    virtual int holdCount() const final;

    /**
     * @brief Returns boolean based on wheter the building can or can't be
     * placed on a Tile-object.
     * @param target is a pointer to the target Tile.
     * @return
     * True - Base class' method return true and Tile has space for building.
     * False - If both conditions are not met.
     * @note Override to modify placementrules for derived classes.
     */
    virtual bool canPlaceOnTile(const std::shared_ptr<TileBase> &target) const;

private:
    int m_hold;

}; // class BuildingBase

} // namespace Course


#endif // BUILDINGBASE_H
