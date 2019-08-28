#include "placeablegameobject.h"
#include "exceptions/expiredpointer.h"
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
    return hasSameOwnerAs(target) or not target->getOwner();
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


} // namespace Course
