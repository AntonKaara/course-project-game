#include "interfaces/iobjectmanager.h"
#include "core/gameobject.h"
#include "tiles/tilebase.h"
#include "core/coordinate.h"

#include <memory>
#include <vector>

#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

namespace Aeta {

class ObjectManager : public Course::iObjectManager
{
public:
    ObjectManager();

    // Public members from the docs

    void addTiles (const std::vector<std::shared_ptr<Course::TileBase>> &tiles);
    std::shared_ptr<Course::TileBase> getTile (const Course::Coordinate &coordinate);
    std::shared_ptr<Course::TileBase> getTile (const Course::ObjectId &id);
    std::vector<std::shared_ptr< Course::TileBase>> getTiles (
            const std::vector<Course::Coordinate> &coordinates);

private:
    std::vector<std::shared_ptr<Course::TileBase>> tilevector_ = {};


};
} // namespace Aeta

#endif // OBJECTMANAGER_HH
