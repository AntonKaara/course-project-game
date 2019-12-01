#include "outpost.h"
#include "objectmanager.hh"

namespace Aeta {

Outpost::Outpost(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
                 const std::shared_ptr<Course::iObjectManager> &objectManager,
                 const std::shared_ptr<Course::PlayerBase>& owner,
                 const int& tileSpaces,
                 const Course::ResourceMap& buildCost,
                 const Course::ResourceMap& production):
    BuildingBase(eventHandler,
                 objectManager,
                 owner,
                 tileSpaces,
                 buildCost,
                 production) {

    objectManager_ = std::dynamic_pointer_cast<ObjectManager>(objectManager);
    setDescription("basic", "This outpost guards the surrounding tiles. "
                            "If an outpost is destroyed, the player loses control of the area.");

}

std::string Outpost::getType() const {

    return "Outpost";

}

void Outpost::onBuildAction() {

    std::vector< std::shared_ptr<Course::TileBase> > neighbours =
            objectManager_->getTiles(getCoordinatePtr()->neighbours(2));

    for(auto it = neighbours.begin(); it != neighbours.end(); ++it)
    {
        // If the tile doesn't have owner, set it's owner to buildings owner
        if( not (*it)->getOwner() )
        {
            (*it)->setOwner(getOwner());
        }
    }

}

} // namespace Aeta
