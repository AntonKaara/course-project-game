#include "buildingbase.h"
#include "../exceptions/ownerconflict.h"
#include "../tiles/tilebase.h"


namespace Course {

BuildingBase::BuildingBase(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<iObjectManager> &objectmanager,
        const std::shared_ptr<PlayerBase>& owner,
        const int& tilespaces,
        const int& hold):
    PlaceableGameObject(eventhandler, objectmanager, owner, tilespaces),
    m_hold(hold)
{
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

bool BuildingBase::canPlaceOnTile(const std::shared_ptr<TileBase> &target) const
{
    return PlaceableGameObject::canPlaceOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity());
}

} // namespace Course
