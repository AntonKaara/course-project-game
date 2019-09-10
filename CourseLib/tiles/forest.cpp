#include "forest.h"


namespace Course {

static const ResourceMap FOREST_PRODUCTION = {
    {MONEY, 1},
    {FOOD, 2},
    {WOOD, 3},
    {STONE, 0},
    {ORE, 0},
};

Forest::Forest(const Coordinate& location,
               const std::shared_ptr<iGameEventHandler>& eventhandler,
               const std::shared_ptr<iObjectManager>& objectmanager):
    TileBase(location, eventhandler, objectmanager,FOREST_PRODUCTION)
{
}

std::string Forest::getType() const
{
    return "Forest";
}

void Forest::addBuilding(const std::shared_ptr<BuildingBase>& building)
{
    TileBase::addBuilding(building);
    building->addHoldMarkers(1);
}

} // namespace Course
