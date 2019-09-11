#include "grassland.h"


namespace Course {


Grassland::Grassland(const Coordinate& location,
                     const std::shared_ptr<iGameEventHandler>& eventhandler,
                     const std::shared_ptr<iObjectManager>& objectmanager):
    TileBase(location, eventhandler, objectmanager)
{
}

std::string Grassland::getType() const
{
    return "Grassland";
}

} // namespace Course
