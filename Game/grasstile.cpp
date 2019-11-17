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
             production) {
    setDescription("basic", "Fertile land suits well for farming. Incredibly flat.");
}

std::string GrassTile::getType() const {

    return "Grass";

}

} // namespace Aeta
