#ifndef IGAMEEVENTHANDLER_H
#define IGAMEEVENTHANDLER_H

#include <memory>

#include "../../BGBase/source/playerbase.h"
#include "../../BGBase/source/gameobject.h"
#include "../basicresources.h"


namespace Course {

/**
 * @brief The iGameEventHandler class is an interface for Course-side code to
 * interact with GameEventHandler implemented by the students.
 *
 * @note The interface lists only functions that the course-side requires.
 * The actual implementation can and should contain more stuff.
 * @note In "real" project EventHandler should be a singleton and not
 * (in C++'s case actually can't) use Abstract class to define the interface
 * for it. <b>This design was chosen merely for pedagogical reasons and
 * give students more freedom in their project design.</b>
 */
class iGameEventHandler
{
public:
    iGameEventHandler() = delete;
    virtual ~iGameEventHandler() = delete;

    /**
     * @brief modifyResource modify player's resources. Can be used to both
     * sum or subtract.
     * @param resource defines the resource that is being modified
     * @param amount defines the amount that is being altered
     * @param player defines the player that is being effected
     * @post Exception guarantee: Basic
     * @exception BGBase::ExpiredPointer - If the player has expired.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    virtual bool modifyResource(BasicResource resource,
                                int amount,
                                std::weak_ptr<BGBase::PlayerBase> player) = 0;

    /**
     * @brief destroyObject removes objects.
     * @param object weak-pointer to the object that is being destroyed.
     * @post Exception guarantee: Basic
     * @exception BGBase::ExpiredPointer - If the weak-pointer has expired.
     */
    virtual void destroyObject(std::weak_ptr<BGBase::GameObject> object) = 0;
};

}
#endif // IGAMEEVENTHANDLER_H
