#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"

#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "player.hh"

#ifndef FARM_H
#define FARM_H

namespace Aeta {

class Farm : public Course::BuildingBase {

public:

    Farm(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
         const std::shared_ptr<Course::iObjectManager> &objectManager,
         const std::shared_ptr<Player>& owner,
         const int& tileSpaces = 1,
         const Course::ResourceMap& buildCost = {},
         const Course::ResourceMap& production = {});

    std::string getType() const override;

};

} // namespace Aeta

#endif // FARM_H
