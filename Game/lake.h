#ifndef LAKE_H
#define LAKE_H

#include "tiles/tilebase.h"

namespace Aeta {

class Lake : public Course::TileBase {

public:

    Lake(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 1,
         const unsigned int& max_work = 1,
         const Course::ResourceMap& production = {});

    std::string getType() const override;

};

} // namespace Aeta

#endif // LAKE_H
