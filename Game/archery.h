#ifndef ARCHERY_H
#define ARCHERY_H

#include "unitbase.h"

namespace Aeta {

/**
 * @brief The Archery class represents the archer unit in the game.
 *
 * It has its own stats and the necessary overrides compared to UnitBase.
 */
class Archery : public UnitBase {

public:

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the games's GameEventHandler.
     * @param objectmanager points to the games's ObjectManager
     * @param owner points to the owning player.
     * @param tilespaces point to the amount of spaces taken.
     * @param cost has the cost of the unit listed as a resourcemap.
     * @param efficiency has the cost of the unit listed as a resourcemap.
     *
     */
    Archery(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
            const std::shared_ptr<Course::iObjectManager> &objectmanager,
            const std::shared_ptr<Course::PlayerBase> &owner, const int &tilespaces,
            const Course::ResourceMap &cost,
            const Course::ResourceMapDouble &efficiency);

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Resets the movement points to a unit specific value.
     */
    virtual void resetMovement() override;

};

} // namespace Aeta


#endif // ARCHERY_H
