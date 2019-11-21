#include "buildings/buildingbase.h"

#include <QObject>

#ifndef LUMBERMILL_H
#define LUMBERMILL_H

namespace Aeta {

class Lumbermill : public Course::BuildingBase {

public:

    Lumbermill(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
               const std::shared_ptr<Course::iObjectManager> &objectManager,
               const std::shared_ptr<Course::PlayerBase>& owner,
               const int& tileSpaces = 1,
               const Course::ResourceMap& buildCost = {},
               const Course::ResourceMap& production = {});

    std::string getType() const override;
    void onBuildAction() override;

private:

    std::shared_ptr<Course::iObjectManager> objectManager_;

};

} // namespace Aeta

#endif // LUMBERMILL_H
