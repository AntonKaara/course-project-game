#include "interfaces/iobjectmanager.h"
#include "core/gameobject.h"

#include <memory>
#include <vector>


#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

namespace Aeta {
class ObjectManager : public Course::iObjectManager
{
public:
    ObjectManager();

    // Dokumentaatiosta otetut public memberit

    void addTiles (const std::vector<std::shared_ptr<Course::TileBase>> &tiles)=0;
    std::shared_ptr<Course::TileBase> getTile (const Course::Coordinate &coordinate)=0;
    std::shared_ptr<Course::TileBase> getTile (const Course::ObjectId &id)=0;
    std::vector<std::shared_ptr< Course::TileBase>> getTiles (const std::vector<Course::Coordinate> &coordinates)=0;

private:
    std::vector<std::shared_ptr<Course::TileBase>> tilevector_ = {};


};
} // namespace Aeta

#endif // OBJECTMANAGER_HH
