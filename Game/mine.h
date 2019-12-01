#ifndef MINE_H
#define MINE_H

#include "buildings/buildingbase.h"

#include <QObject>

namespace Aeta {

/**
 * @brief The Mine class represents a mine building in the game
 */
class Mine : public Course::BuildingBase {

public:

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param objectmanager points to the games's ObjectManager
     * @param owner points to the owning player.
     * @param tilespaces points to the amount of spaces taken.
     * @param buildCost has the cost of the building listed as a resourcemap.
     * @param production has the production per turn listed as a resourcemap.
     */
    Mine(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
         const std::shared_ptr<Course::iObjectManager> &objectManager,
         const std::shared_ptr<Course::PlayerBase>& owner,
         const int& tileSpaces = 1,
         const Course::ResourceMap& buildCost = {},
         const Course::ResourceMap& production = {});

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

private:

    std::shared_ptr<Course::iObjectManager> objectManager_;

};

} // namespace Aeta

#endif // MINE_H
