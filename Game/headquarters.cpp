#include "headquarters.h"

namespace Aeta {

Headquarters::Headquarters(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
                           const std::shared_ptr<Course::iObjectManager> &objectManager,
                           const std::shared_ptr<Course::PlayerBase>& owner,
                           const int& tileSpaces,
                           const Course::ResourceMap& buildCost,
                           const Course::ResourceMap& production):
    BuildingBase(eventHandler,
                 objectManager,
                 owner,
                 tileSpaces,
                 buildCost,
                 production) {

}

//Headquarters::Headquarters(const Headquarters &otherHq(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
//                                                       const std::shared_ptr<Course::iObjectManager> &objectManager,
//                                                       const std::shared_ptr<Course::PlayerBase>& owner,
//                                                       const int& tileSpaces,
//                                                       const Course::ResourceMap& buildCost,
//                                                       const Course::ResourceMap& production)) {
//}

std::string Headquarters::getType() const {

    return "headquarters";

}

} // namespace Aeta
