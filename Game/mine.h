#include "buildings/buildingbase.h"

#include <QObject>

#ifndef MINE_H
#define MINE_H

namespace Aeta {

class Mine : public Course::BuildingBase {

public:

    Mine(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
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

#endif // MINE_H
