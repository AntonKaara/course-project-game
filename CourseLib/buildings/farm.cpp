#include "farm.h"


namespace Course {


const ResourceMap Farm::BUILD_COST = {
    {BasicResource::MONEY, 250},
    {BasicResource::FOOD, 50},
    {BasicResource::WOOD, 50},
    {BasicResource::STONE, 10}
};

const ResourceMap Farm::PRODUCTION_EFFECT = {
    {BasicResource::FOOD, 2}
};

Farm::Farm(const std::shared_ptr<iGameEventHandler>& eventhandler,
           const std::shared_ptr<iObjectManager>& objectmanager,
           const std::shared_ptr<PlayerBase>& owner
           ):
    BuildingBase(
        eventhandler,
        objectmanager,
        owner
        )
{
}

std::string Farm::getType() const
{
    return "Farm";
}

const ResourceMap Farm::getProduction()
{
    if( holdCount() > 0 )
    {
        addHoldMarkers(-1);
        return {};
    }
    return Farm::PRODUCTION_EFFECT;
}

} // namespace Course
