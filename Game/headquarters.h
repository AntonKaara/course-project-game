#ifndef HEADQUARTERS_H
#define HEADQUARTERS_H

#include "buildings/buildingbase.h"

#include <QObject>

namespace Aeta {

class Headquarters : public Course::BuildingBase {

public:
    /**
     * @brief Disabled default constructor.
     */
    Headquarters() = delete;

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
    Headquarters(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
                 const std::shared_ptr<Course::iObjectManager> &objectManager,
                 const std::shared_ptr<Course::PlayerBase>& owner,
                 const int& tileSpaces = 1,
                 const Course::ResourceMap& buildCost = {},
                 const Course::ResourceMap& production = {});

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

    /**
     * @brief Conquers neighboring tiles when built.
     */
    void onBuildAction() override;

    /**
     * @brief Returns the HQ Health.
     * @return Hitpoints/health as integer
     */
    int getHitPoints();

    /**
     * @brief Sets the HQ hitpoints to a given value
     */
    void setHitPoints(int hitPoints);

    /**
     * @brief Changes the HQ hitpoints by a given value
     */
    void changeHitPoints(int amount);

private:

    std::shared_ptr<Course::iObjectManager> objectManager_;
    int hitPoints_ = 100;

};

} // namespace Aeta

#endif // HEADQUARTERS_H
