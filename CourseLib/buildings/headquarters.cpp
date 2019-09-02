#include "headquarters.h"
#include "tiles/tilebase.h"


namespace Course {


const ResourceMap HeadQuarters::BUILD_COST = {
    {BasicResource::MONEY, 1000},
    {BasicResource::FOOD, 500},
    {BasicResource::WOOD, 300},
    {BasicResource::STONE, 200},
    {BasicResource::ORE, 100}
};

const ResourceMap HeadQuarters::PRODUCTION_EFFECT = {
    {BasicResource::MONEY, 50}
};


HeadQuarters::HeadQuarters(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<iObjectManager>& objectmanager,
        const std::shared_ptr<PlayerBase>& owner
        ):
    BuildingBase(eventhandler, objectmanager, owner, 1)
{
}

std::string HeadQuarters::getType()
{
    return "HeadQuarters";
}

void HeadQuarters::onBuildAction()
{
    std::vector< std::shared_ptr<TileBase> > neighbours;

    lockObjectManager()->getTiles(getCoordinate()->neighbours(3));

    for(auto it = neighbours.begin(); it != neighbours.end(); ++it)
    {
        // If the Tile doesn't have owner, set it's owner to buildings owner.
        if( not (*it)->getOwner() )
        {
            (*it)->setOwner(getOwner());
        }
    }
}

const ResourceMap HeadQuarters::getProduction()
{
    if( holdCount() > 0)
    {
        addHoldMarkers(-1);
        return {};
    }
    return HeadQuarters::PRODUCTION_EFFECT;
}


} // namespace Course
