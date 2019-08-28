#include "farm.h"


namespace Course {

Farm::Farm(const std::shared_ptr<iGameEventHandler>& eventhandler,
           const std::shared_ptr<iObjectManager>& objectmanager,
           const std::shared_ptr<PlayerBase>& owner,
           const std::shared_ptr<TileBase>& tile
           ):
    BuildingBase(eventhandler, objectmanager, owner, tile)
{
}

std::string Farm::getType() const
{
    return "Farm";
}

void Farm::doAction()
{
}

double Farm::getMultiplier(BasicResource /*resource*/) const
{
    return 0;
}

int Farm::getProduction(BasicResource resource) const
{
    return (resource == BasicResource::FOOD ? 2 : 0);
}

} // namespace Course
