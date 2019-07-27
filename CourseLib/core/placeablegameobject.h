#ifndef PLACEABLEGAMEOBJECT_H
#define PLACEABLEGAMEOBJECT_H

#include "gameobject.h"
#include "basicresources.h"


namespace Course {

class TileBase;

/**
 * @brief The PlaceableGameObject class represents GameObjects that can be
 * placed on Tile Objects.
 *
 * Main purpose for this class is to wrap location-setting and
 * GameEventHandler locking/invariant -checking.
 *
 * @invariant Weak-pointer to GameEventHandler hasn't expired.
 */
class PlaceableGameObject : public GameObject
{
public:
    /**
     * @brief Disabled default constructor.
     */
    PlaceableGameObject() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param descriptions contains descriptions and flavor texts.
     * @param tile points to the tile upon which the building is constructed.
     */
    explicit PlaceableGameObject(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<iObjectManager>& objectmanager,
            const std::shared_ptr<PlayerBase>& owner,
            const DescriptionMap& descriptions = {},
            const std::shared_ptr<TileBase>& tile = {}
            );

    /**
     * @brief Default destructor.
     */
    virtual ~PlaceableGameObject() = default;

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

    /**
     * @brief How many spaces does the GameObject take from a Tile's capacity.
     * @return Amount of spaces that are taken.
     * @post Exception guarantee: No-throw
     */
    virtual unsigned int spacesInTileCapacity() const;

    /**
     * @brief Check if the object can be placed on the target tile.
     * @param target points to the tile that is being checked.
     * @return
     * True - Building can be placed on the target \n
     * False - Building can't be placed on the target
     * @post Exception guarantee: Strong
     */
    virtual bool canPlaceOnTile(const std::shared_ptr<TileBase>& target) const;

    /**
     * @brief Set the PlaceableGameObject's location.
     * @param tile points to the Tile where the object is placed.
     * @post Exception guarantee: No-throw
     * @note nullptr can be used to clear the location.
     */
    virtual void setLocationTile(const std::shared_ptr<TileBase>& tile) final;

private:
    std::weak_ptr<TileBase> m_location;

}; // class PlaceableGameObject

} // namespace Course


#endif // PLACEABLEGAMEOBJECT_H
