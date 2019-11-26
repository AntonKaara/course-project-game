#ifndef OUTPOST_H
#define OUTPOST_H

#include "buildings/buildingbase.h"
#include "objectmanager.hh"

namespace Aeta {

class Outpost : public Course::BuildingBase {

public:

    Outpost() = delete;
    Outpost(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
            const std::shared_ptr<Course::iObjectManager> &objectManager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tileSpaces = 1,
            const Course::ResourceMap& buildCost = {},
            const Course::ResourceMap& production = {});

    std::string getType() const override;
    void onBuildAction() override;

private:

    std::shared_ptr<ObjectManager> objectManager_ = nullptr;

};

} // namespace Aeta

#endif // OUTPOST_H
