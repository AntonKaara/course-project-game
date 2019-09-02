#include "outpost.h"
#include "interfaces/iobjectmanager.h"

namespace Course {


const ResourceMap Outpost::BUILD_COST = {
    {BasicResource::MONEY, 250},
    {BasicResource::FOOD, 100},
    {BasicResource::WOOD, 75},
    {BasicResource::STONE, 25}
};

const ResourceMap Outpost::PRODUCTION_EFFECT = {
    {BasicResource::MONEY, -10}
};

Outpost::Outpost(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<iObjectManager>& objectmanager,
        const std::shared_ptr<PlayerBase>& owner
        ):
    BuildingBase(eventhandler, objectmanager, owner, 1)
{
}

std::string Outpost::getType()
{
    return "Outpost";
}

void Outpost::doSpecialAction()
{
}

void Outpost::onBuildAction()
{
    std::vector< std::shared_ptr<TileBase> > neighbours;

    lockObjectManager()->getTiles(getCoordinate()->neighbours(1));

    for(auto it = neighbours.begin(); it != neighbours.end(); ++it)
    {
        // If the Tile doesn't have owner, set it's owner to buildings owner.
        if( not (*it)->getOwner() )
        {
            (*it)->setOwner(getOwner());
        }
    }
}

const ResourceMap Outpost::getProduction()
{
    if( holdCount() < 0)
    {
        addHoldMarkers(-1);
        return {};
    }
    return Outpost::PRODUCTION_EFFECT;
}

} // namespace Course
