#ifndef PLACEABLEGAMEOBJECT_H
#define PLACEABLEGAMEOBJECT_H

#include "gameobject.h"


namespace Course {

class TileBase;

/**
 * @brief The PlaceableGameObject class represents GameObjects that can be
 * placed on Tile Objects.
 *
 * Contains methods for automatically checking if a GameObject can be placed
 * on a Tile.
 *
 * Override functions canPlaceOnTile to change class-specific placement-rules.
 *
 * @note Overridable methods have strong exception guarantees. So you don't
 * have to force no-throw in your own implementations.
 */
class PlaceableGameObject : public GameObject
{
public:
    const int TILESPACES;

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
            const int& tilespace = 1
            );

    /**
     * @brief Default destructor.
     */
    virtual ~PlaceableGameObject() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief How many spaces does the GameObject take from a Tile's capacity.
     * @return Amount of spaces that is being taken.
     * @post Exception guarantee: No-throw
     */
    virtual int spacesInTileCapacity() const final;

    /**
     * @brief Check if the object can be placed on the target tile.
     * @param target is a pointer to the tile that is being checked.
     * @return
     * True - Object has same owner as the tile.
     * False - If condition doesn't match.
     * @post Exception guarantee: Strong
     * @note Override to change default behaviour
     */
    virtual bool canBePlacedOnTile(const std::shared_ptr<TileBase>& target) const;

    /**
     * @brief Set the PlaceableGameObject's location.
     * @param tile points to the Tile where the object is placed.
     * @post Exception guarantee: Strong
     * @note nullptr can be used to clear the location.
     * @exception
     * OwnerConflict - If the object't and tile's ownership conflicted.
     */
    virtual void setLocationTile(const std::shared_ptr<TileBase>& tile);

    /**
     * @brief Returns a shared_ptr to current lcoation-tile.
     * @return
     * @post Exception guarantee: No-throw
     */
    virtual std::shared_ptr<TileBase> currentLocationTile() const final;

private:
    std::weak_ptr<TileBase> m_location;

}; // class PlaceableGameObject

} // namespace Course


#endif // PLACEABLEGAMEOBJECT_H
