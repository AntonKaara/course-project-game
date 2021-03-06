﻿#include "foresttile.h"

namespace Aeta {

ForestTile::ForestTile(const Course::Coordinate& location,
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
    setDescription("basic", "Forested land provides you with some wood. Don't get lost in the forest!");

}

std::string ForestTile::getType() const {

    return "Forest";

}

} // namespace Aeta
