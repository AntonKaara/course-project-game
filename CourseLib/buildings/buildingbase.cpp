#include "buildingbase.h"
#include "../exceptions/ownerconflict.h"
#include "../tiles/tilebase.h"


namespace Course {

const ResourceMap BuildingBase::BUILD_COST = {};
const ResourceMap BuildingBase::PRODUCTION_EFFECT = {};



BuildingBase::BuildingBase(const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<iObjectManager> &objectmanager,
        const std::shared_ptr<PlayerBase>& owner,
        const int& tilespaces):
    PlaceableGameObject(eventhandler, objectmanager, owner, tilespaces),
    m_hold(0)
{
}

std::string BuildingBase::getType()
{
    return "BuildingBase";
}

void BuildingBase::doSpecialAction()
{
    // By default buildings have no actions.
}

void BuildingBase::onBuildAction()
{
    // By default buildings have no actions after building.
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
