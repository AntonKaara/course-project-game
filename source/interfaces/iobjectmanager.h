#ifndef IOBJECTMANAGER_H
#define IOBJECTMANAGER_H

#include <memory>

#include "../buildings/buildingbase.h"
#include "../tiles/tilebase.h"
#include "../workers/workerbase.h"

namespace Course {

/**
 * @brief The iObjectManager class is an interface for Course-side code to
 * interact with ObjectManager implemented by the students.
 *
 * @note The interface lists only functions that the course-side requires.
 * The actual implementation can and should contain more stuff.
 */
class iObjectManager
{
public:
    iObjectManager() = delete;
    virtual ~iObjectManager() = delete;

    /**
     * @brief addTiles Adds new tiles to the ObjectManager
     * @param tiles reference to a vector of shared pointers to new tiles.
     */
    virtual void addTiles(std::vector<std::shared_ptr<TileBase> >& tiles) = 0;

};

}

#endif // IOBJECTMANAGER_H
