#include "headquarters.h"

namespace Aeta {

Headquarters::Headquarters(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
                           const std::shared_ptr<Course::iObjectManager> &objectManager,
                           const std::shared_ptr<Player>& owner,
                           const int& tileSpaces,
                           const Course::ResourceMap& buildCost,
                           const Course::ResourceMap& production)

    : BuildingBase(eventHandler, objectManager, owner, tileSpaces, buildCost, production)
{

}

std::string Headquarters::getType() const
{
    return "headquarters";
}

} // namespace Aeta
