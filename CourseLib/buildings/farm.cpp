#include "farm.h"


namespace Course {

Farm::Farm(const std::shared_ptr<iGameEventHandler>& eventhandler,
           const std::shared_ptr<iObjectManager>& objectmanager,
           const std::shared_ptr<PlayerBase>& owner
           ):
    BuildingBase(eventhandler, objectmanager, owner, 1)
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

const std::map<BasicResource, int> Farm::buildingCost() const
{
    return std::map<BasicResource, int>({
                    {BasicResource::FOOD, 50},
                    {BasicResource::WOOD, 50},
                    {BasicResource::STONE, 10}
    });
}

} // namespace Course
