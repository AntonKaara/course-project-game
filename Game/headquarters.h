#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "core/playerbase.h"

#ifndef HEADQUARTERS_H
#define HEADQUARTERS_H

#include <QObject>

namespace Aeta {

class Headquarters : public Course::BuildingBase {

public:

    Headquarters() = delete;

    // Constructor

    Headquarters(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
                 const std::shared_ptr<Course::iObjectManager> &objectManager,
                 const std::shared_ptr<Course::PlayerBase>& owner,
                 const int& tileSpaces = 1,
                 const Course::ResourceMap& buildCost = {},
                 const Course::ResourceMap& production = {});

    std::string getType() const override;

};

} // namespace Aeta

#endif // HEADQUARTERS_H
