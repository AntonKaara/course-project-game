#ifndef FARM_H
#define FARM_H

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"

#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "player.hh"

namespace Aeta {

/**
 * @brief The Farm class represents a farm-building in the game.
 *
 */
class Farm : public Course::BuildingBase {

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
    Farm(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
         const std::shared_ptr<Course::iObjectManager> &objectManager,
         const std::shared_ptr<Course::PlayerBase>& owner,
         const int& tileSpaces = 1,
         const Course::ResourceMap& buildCost = {},
         const Course::ResourceMap& production = {});

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;


};

} // namespace Aeta

#endif // FARM_H
