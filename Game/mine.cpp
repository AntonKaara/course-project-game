#include "mine.h"
#include "objectmanager.hh"

namespace Aeta {

Mine::Mine(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
           const std::shared_ptr<Course::iObjectManager> &objectManager,
           const std::shared_ptr<Course::PlayerBase>& owner,
           const int& tileSpaces,
           const Course::ResourceMap& buildCost,
           const Course::ResourceMap& production)
    : BuildingBase(eventHandler,
                   objectManager,
                   owner,
                   tileSpaces,
                   buildCost,
                   production) {

    objectManager_ = objectManager;
    setDescription("basic", "MINECRAFT");


}

std::string Mine::getType() const {

    return "Mine";

}

void Mine::onBuildAction() {

}

} // namespace Aeta
