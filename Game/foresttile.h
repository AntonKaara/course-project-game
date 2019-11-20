#include "tiles/tilebase.h"

#include "objectmanager.hh"

#include <string>

#ifndef FORESTTILE_H
#define FORESTTILE_H

namespace Aeta {

class ForestTile : public Course::TileBase
{
public:

    ForestTile() = delete;

    ForestTile(const Course::Coordinate& location,
               const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
               const std::shared_ptr<Course::iObjectManager>& objectmanager,
               const unsigned int& max_build = 1,
               const unsigned int& max_work = 0,
               const Course::ResourceMap& production =
                    Course::ConstResourceMaps::FOREST_BP);

    virtual ~ForestTile() override = default;

    virtual std::string getType() const override;

};

} // namespace Aeta
#endif // FORESTTILE_H
