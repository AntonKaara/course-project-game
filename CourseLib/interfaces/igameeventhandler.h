#ifndef IGAMEEVENTHANDLER_H
#define IGAMEEVENTHANDLER_H

#include <memory>
#include <vector>

#include "core/basicresources.h"

namespace Course {
class TileBase;
class PlayerBase;
class GameObject;
class Coordinate;
/**
 * @brief The iGameEventHandler class is an interface which the Course-side
 * code uses to interact with the GameEventHandler implemented by the students.
 *
 * @note The interface declares only functions required by the Course-side code.
 * The actual implementation can (and should!) contain more stuff.
 * @note In a "real" project, the GameEventHandler should be a singleton
 * and not use an abstract base class to define the interface for it.
 * <b>This design was chosen merely for pedagogical reasons and to
 * give students more freedom in their project design.</b>
 */
class iGameEventHandler
{
public:
    /**
     * @brief Default destructor.
     */
    virtual ~iGameEventHandler() = default;

    /**
     * @brief Modify a player's resources. Can be used to both sum or subtract.
     * @param player points to the affected player.
     * @param resource defines the modified resource.
     * @param amount defines the altered amount.
     * @post Exception guarantee: Basic
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    virtual bool modifyResource(std::shared_ptr<PlayerBase> player,
                                BasicResource resource,
                                int amount) = 0;

    /**
     * @brief Removes objects from the game.
     * @param object points to the object being destroyed.
     * @post Exception guarantee: Basic
     */
    virtual void destroyObject(std::shared_ptr<GameObject> object) = 0;

    virtual std::vector< std::shared_ptr<TileBase> > getTiles(
            std::vector<Coordinate> coordinates) = 0;

}; // class iGameEventHandler

} // namespace Course


#endif // IGAMEEVENTHANDLER_H
