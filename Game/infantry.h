#ifndef INFANTRY_H
#define INFANTRY_H

#include "unitbase.h"

namespace Aeta {

/**
 * @brief The Infrantry class represents the foot unit in the game.
 *
 * It has its own stats and the necessary overrides compared to UnitBase.
 */
class Infantry : public UnitBase {

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
    Infantry(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
             const std::shared_ptr<Course::iObjectManager> &objectmanager,
             const std::shared_ptr<Course::PlayerBase> &owner, const int &tilespaces,
             const Course::ResourceMap &cost,
             const Course::ResourceMapDouble &efficiency);

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

};

} // namespace Aeta

#endif // INFANTRY_H
