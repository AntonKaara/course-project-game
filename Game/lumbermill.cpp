#include "lumbermill.h"
#include "objectmanager.hh"

namespace Aeta {

Lumbermill::Lumbermill(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
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
    setDescription("basic", "Niin hyvää puuta.");


}

std::string Lumbermill::getType() const {

    return "Lumbermill";

}

void Lumbermill::onBuildAction() {

}

} // namespace Aeta
