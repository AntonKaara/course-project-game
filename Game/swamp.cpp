#include "swamp.h"

namespace Aeta {

Swamp::Swamp(const Course::Coordinate& location,
             const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
             const std::shared_ptr<Course::iObjectManager>& objectmanager,
             const unsigned int& max_build,
             const unsigned int& max_work,
             const Course::ResourceMap& production)
    : TileBase(location,
               eventhandler,
               objectmanager,
               max_build,
               max_work,
               production){
    setDescription("basic", "Moist land, and hard to walk through! Can't build anything on it. Sad.");

}

std::string Swamp::getType() const {

    return "Swamp";

}

} // namespace Aeta
