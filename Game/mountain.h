#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include "tiles/tilebase.h"

namespace Aeta {

class Mountain : public Course::TileBase {

public:

    Mountain(const Course::Coordinate& location,
             const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
             const std::shared_ptr<Course::iObjectManager>& objectmanager,
             const unsigned int& max_build = 0,
             const unsigned int& max_work = 0,
             const Course::ResourceMap& production = {});

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

};

} // namespace Aeta

#endif // MOUNTAIN_H
