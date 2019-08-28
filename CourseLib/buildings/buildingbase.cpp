#include "buildingbase.h"
#include "../exceptions/ownerconflict.h"
#include "../tiles/tilebase.h"


namespace Course {

BuildingBase::BuildingBase(const std::shared_ptr<iGameEventHandler>& eventhandler, const std::shared_ptr<iObjectManager> &objectmanager,
        const std::shared_ptr<PlayerBase>& owner,
        const std::shared_ptr<TileBase>& tile,
        int hold):
    PlaceableGameObject(eventhandler, objectmanager, owner, tile),
    m_hold(hold)
{
    if (not canPlaceOnTile(tile))
    {
        throw OwnerConflict("Another player owns this tile!");
    }
}

std::string BuildingBase::getType() const
{
    return "BuildingBase";
}

void BuildingBase::doAction()
{
    // By default buildings have no actions.
}

void BuildingBase::buildAction()
{
    // By default buildings have no actions after building.
}

double BuildingBase::getMultiplier(BasicResource) const
{
    // By default buildings don't have any effect on production.
    return 0;
}

int BuildingBase::getProduction(BasicResource) const
{
    // By default buildings don't have any effect on production.
    return 0;
}

void BuildingBase::addHoldMarkers(int amount)
{
    m_hold += amount;
}

int BuildingBase::holdCount() const
{
    return m_hold;
}

} // namespace Course
