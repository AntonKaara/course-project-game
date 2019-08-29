#include "headquarters.h"
#include "tiles/tilebase.h"


namespace Course {

HeadQuarters::HeadQuarters(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<iObjectManager>& objectmanager,
        const std::shared_ptr<PlayerBase>& owner
        ):
    BuildingBase(eventhandler, objectmanager, owner, 1)
{
}

std::string HeadQuarters::getType() const
{
    return "HeadQuarters";
}

void HeadQuarters::buildAction()
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

const std::map<BasicResource, int> HeadQuarters::buildingCost() const
{
    return std::map<BasicResource, int>({
                    {BasicResource::FOOD, 500},
                    {BasicResource::WOOD, 300},
                    {BasicResource::STONE, 150},
                    {BasicResource::ORE, 50}
    });
}

} // namespace Course
