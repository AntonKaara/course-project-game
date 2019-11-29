#include "mountain.h"


namespace Aeta {

Mountain::Mountain(const Course::Coordinate& location,
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
    setDescription("basic", "Only the mightiest of wizards can survive in this"
                            " environment. Don't even think about climbing.");
}

std::string Mountain::getType() const {

    return "Mountain";

}

} // namespace Aeta
