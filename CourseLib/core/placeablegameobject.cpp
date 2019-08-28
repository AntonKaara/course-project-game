#include "placeablegameobject.h"
#include "tiles/tilebase.h"


namespace Course {

PlaceableGameObject::PlaceableGameObject(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<iObjectManager>& objectmanager,
        const std::shared_ptr<PlayerBase>& owner,
        const std::shared_ptr<TileBase>& tile):
    GameObject(owner, eventhandler, objectmanager),
    m_location(tile)
{
    if( tile )
    {
        setCoordinate(tile->getCoordinate());
    }
}

std::string PlaceableGameObject::getType() const
{
    return "PlaceableGameObject";
}

int PlaceableGameObject::spacesInTileCapacity() const
{
    return 1;
}

bool PlaceableGameObject::canPlaceOnTile(
        const std::shared_ptr<TileBase>& target) const
{
    if( target->getOwner() == nullptr or getOwner() == nullptr )
    {
        return true;
    }

    return hasSameOwnerAs(target);
}

void PlaceableGameObject::setLocationTile(const std::shared_ptr<TileBase>& tile)
{
    m_location = tile;
    if (tile)
    {
        setCoordinate(tile->getCoordinate());
    }
    else
    {
        unsetCoordinate();
    }
}

std::shared_ptr<TileBase> PlaceableGameObject::currentLocationTile() const
{
    return m_location.lock();
}


} // namespace Course
