#include "grassland.h"


namespace Course {

static const ProductionMap GRASSLAND_PRODUCTION = {
    {MONEY, 1},
    {FOOD, 2},
    {WOOD, 1},
    {STONE, 0},
    {ORE, 0},
};

Grassland::Grassland(const Coordinate& location,
                     const std::shared_ptr<iGameEventHandler>& eventhandler,
                     const std::shared_ptr<iObjectManager>& objectmanager):
    TileBase(location, eventhandler, objectmanager, GRASSLAND_PRODUCTION)
{
}

std::string Grassland::getType() const
{
    return "Grassland";
}

} // namespace Course
