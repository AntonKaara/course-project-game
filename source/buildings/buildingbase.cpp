
#include "buildingbase.h"
#include "../../BGBase/source/exceptions/expiredpointer.h"

namespace Course {

BuildingBase::BuildingBase(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<BGBase::PlayerBase>& owner,
        const BGBase::Description_map& descriptions,
        const std::shared_ptr<TileBase>& tile,
        const int& hold):
    PlaceableGameObject(eventhandler, owner, descriptions, tile),
    m_hold(hold)
{
}

void BuildingBase::doAction()
{
}

double BuildingBase::getMultiplier(BasicResource) const
{
    return 0;
}

int BuildingBase::getProduction(BasicResource) const
{
    return 0;
}

std::string BuildingBase::getType() const
{
    return "BuildingBase";
}

void BuildingBase::addHoldMarkers(int amount)
{
    m_hold += amount;
}

int BuildingBase::holdCount()
{
    return m_hold;
}

}
