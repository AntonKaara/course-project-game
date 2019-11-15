#include "grasstile.h"

namespace Aeta {

GrassTile::GrassTile(const Course::Coordinate& location,
                     const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                     const std::shared_ptr<Course::iObjectManager>& objectmanager,
                     const unsigned int& max_build,
                     const unsigned int& max_work,
                     const Course::ResourceMap& production):
    TileBase(location,
             eventhandler,
             objectmanager,
             max_build,
             max_work,
             production)
{
}

std::string GrassTile::getType() const
{
    std::vector<std::shared_ptr<Course::BuildingBase>> buildings = this->getBuildings();
    if (this->getBuildingCount() > 0) {
        if (buildings.at(0)->getType() == "headquarters") {
            return "headquarters";
        }
    }
    return "grasstile";
}
} // namespace Aeta
