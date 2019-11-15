#include "buildings/buildingbase.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "core/resourcemaps.h"
#include "player.hh"

#ifndef HEADQUARTERS_H
#define HEADQUARTERS_H

#include <QObject>

namespace Aeta {

class Headquarters : public Course::BuildingBase
{
public:
    Headquarters() = delete;

    // Constructor
    Headquarters(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
                 const std::shared_ptr<Course::iObjectManager> &objectManager,
                 const std::shared_ptr<Player>& owner,
                 const int& tileSpaces = 1,
                 const Course::ResourceMap& buildCost = {},
                 const Course::ResourceMap& production = {});

    std::string getType() const;
};

} // namespace Aeta

#endif // HEADQUARTERS_H
