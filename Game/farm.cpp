#include "farm.h"

namespace Aeta {

Farm::Farm(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
           const std::shared_ptr<Course::iObjectManager> &objectManager,
           const std::shared_ptr<Player>& owner,
           const int& tileSpaces,
           const Course::ResourceMap& buildCost,
           const Course::ResourceMap& production)
    : BuildingBase(eventHandler,
                   objectManager,
                   owner,
                   tileSpaces,
                   buildCost,
                   production) {

}

std::string Farm::getType() const {

    return "farm";

}

} // namespace Aeta
