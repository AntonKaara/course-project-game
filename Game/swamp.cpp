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
    setDescription("basic", "Moist land, not suitable for building. Hard to walk through."
                            " If you assign your soldiers through it'll probably use all"
                            " of their energy.");

}

std::string Swamp::getType() const {

    return "Swamp";

}

} // namespace Aeta
