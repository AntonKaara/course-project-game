#ifndef OUTPOST_H
#define OUTPOST_H

#include "buildings/buildingbase.h"
#include "objectmanager.hh"

namespace Aeta {

/**
 * @brief The Outpost class represents the outpost building in the game
 */
class Outpost : public Course::BuildingBase {

public:

    /**
     * @brief Disabled default contructor.
     */
    Outpost() = delete;

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
    Outpost(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
            const std::shared_ptr<Course::iObjectManager> &objectManager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tileSpaces = 1,
            const Course::ResourceMap& buildCost = {},
            const Course::ResourceMap& production = {});

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;
    void onBuildAction() override;

private:

    std::shared_ptr<ObjectManager> objectManager_ = nullptr;

};

} // namespace Aeta

#endif // OUTPOST_H
