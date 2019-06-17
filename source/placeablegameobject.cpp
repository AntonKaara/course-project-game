#include "placeablegameobject.h"
#include "tiles/tilebase.h"
#include "../BGBase/source/exceptions/expiredpointer.h"

#include <QtGlobal> // For Q_ASSERT

namespace Course {

PlaceableGameObject::PlaceableGameObject(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<BGBase::PlayerBase>& owner,
        const BGBase::Description_map& descriptions,
        const std::shared_ptr<TileBase>& tile):
    BGBase::GameObject(*(tile->getCoordinate()), owner, descriptions),
    m_location(tile),
    EVENTHANDLER(std::weak_ptr<iGameEventHandler>(eventhandler))
{

}

std::string PlaceableGameObject::getType() const
{
    return "PlaceableGameObject";
}

void PlaceableGameObject::setLocationTile(const std::shared_ptr<TileBase>& tile)
{
    m_location = tile;
    if(tile)
    {
        setCoordinate(tile->getCoordinate());
    }
    else
    {
        unsetCoordinate();
    }
}

unsigned int PlaceableGameObject::spacesInTileCapacity()
{
    return 1;
}

bool PlaceableGameObject::canPlaceOnTile(
        const std::shared_ptr<TileBase>& target)
{
    return has_same_owner_as(target);
}

std::shared_ptr<iGameEventHandler> PlaceableGameObject::lockEventHandler()
{
    std::shared_ptr<iGameEventHandler> handler = EVENTHANDLER.lock();
    Q_ASSERT(handler);
    return handler;
}

}
