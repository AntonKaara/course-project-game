#include "tiles/tilebase.h"

#ifndef MOUNTAIN_H
#define MOUNTAIN_H

namespace Aeta {

class Mountain : public Course::TileBase {

public:
    Mountain(const Course::Coordinate& location,
             const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
             const std::shared_ptr<Course::iObjectManager>& objectmanager,
             const unsigned int& max_build = 1,
             const unsigned int& max_work = 1,
             const Course::ResourceMap& production = {});

    std::string getType() const override;
};

} // namespace Aeta

#endif // MOUNTAIN_H
