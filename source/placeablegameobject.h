#ifndef PLACEABLEGAMEOBJECT_H
#define PLACEABLEGAMEOBJECT_H

#include "../BGBase/source/gameobject.h"
#include "interfaces/igameeventhandler.h"

namespace Course {

class TileBase;

/**
 * @brief The PlaceableGameObject class represents GameObjects tha can be
 * placed on Tile Objects.
 *
 * Main purpose for this class is to wrap location-setting and
 * GameEventHandler locking/invariant -checking.
 *
 * @invariant Weak-pointer to GameEventHandler hasn't expired.
 */
class PlaceableGameObject : public BGBase::GameObject
{
public:
    /**
     * @brief Default constructor disabled.
     */
    PlaceableGameObject() = delete;

    /**
     * @brief Constructor for the class
     */
    PlaceableGameObject(const std::shared_ptr<iGameEventHandler>& eventhandler,
                        const std::shared_ptr<BGBase::PlayerBase>& owner,
                        const BGBase::Description_map& descriptions = {},
                        const std::shared_ptr<TileBase>& tile = {});

    /**
     * @brief Default destructor.
     */
    virtual ~PlaceableGameObject() = default;

    /**
     * @copydoc BGBase::GameObject::getType()
     */
    virtual std::string getType() const;

    /**
     * @brief Sets the Objects location-tile
     * @param object is weak-pointer to the Tile where the object is placed.
     * @post Exception guarantee: No-throw
     * @note Empty weak_ptr can be used to reset the location to nothing.
     */
    virtual void setLocationTile(const std::shared_ptr<TileBase>& tile) final;

    /**
     * @brief How many spaces does the GameObject take from Tile's capacity.
     * @return Amount of spaces are taken.
     * @post Exception guarantee: No-throw
     */
    virtual unsigned int spacesInTileCapacity();

    /**
     * @brief Returns if the object can be placed on the target tile.
     * @param target Tile that the is being checked
     * @return
     * True - Building can be placed on the target
     * False - Building can't be placed on the target
     * @post Exception guarantee: Strong
     */
    virtual bool canPlaceOnTile(const std::shared_ptr<TileBase>& target);

protected:
    /**
     * @brief Locks the eventhandler for use and checks the class-invariant.
     * @return Usable shared_ptr to the GameEventHandler.
     */
    virtual std::shared_ptr<iGameEventHandler> lockEventHandler() final;

private:
    std::weak_ptr<TileBase> m_location;

    const std::weak_ptr<iGameEventHandler> EVENTHANDLER;

};

}

#endif // PLACEABLEGAMEOBJECT_H
