#ifndef HEADQUARTERS_H
#define HEADQUARTERS_H

#include "buildings/buildingbase.h"

#include <QObject>

namespace Aeta {

class Headquarters : public Course::BuildingBase {

public:

    Headquarters() = delete;

    Headquarters(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
                 const std::shared_ptr<Course::iObjectManager> &objectManager,
                 const std::shared_ptr<Course::PlayerBase>& owner,
                 const int& tileSpaces = 1,
                 const Course::ResourceMap& buildCost = {},
                 const Course::ResourceMap& production = {});

    std::string getType() const override;
    void onBuildAction() override;

    int getHitPoints();
    void setHitPoints(int hitPoints);
    void changeHitPoints(int amount);

private:

    std::shared_ptr<Course::iObjectManager> objectManager_;
    int hitPoints_ = 100;

};

} // namespace Aeta

#endif // HEADQUARTERS_H
