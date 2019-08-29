#include "outpost.h"
#include "interfaces/iobjectmanager.h"

namespace Course {

Outpost::Outpost(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<iObjectManager>& objectmanager,
        const std::shared_ptr<PlayerBase>& owner
        ):
    BuildingBase(eventhandler, objectmanager, owner, 1)
{
}

std::string Outpost::getType() const
{
    return "Outpost";
}

void Outpost::doAction()
{
}

void Outpost::buildAction()
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

const std::map<BasicResource, int> Outpost::buildingCost() const
{
    return std::map<BasicResource, int>({
                    {BasicResource::FOOD, 100},
                    {BasicResource::WOOD, 75},
                    {BasicResource::STONE, 25}
    });
}

} // namespace Course
