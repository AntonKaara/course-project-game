#include "headquarters.h"
#include "objectmanager.hh"

namespace Aeta {

Headquarters::Headquarters(const std::shared_ptr<Course::iGameEventHandler> &eventHandler,
                           const std::shared_ptr<Course::iObjectManager> &objectManager,
                           const std::shared_ptr<Course::PlayerBase>& owner,
                           const int& tileSpaces,
                           const Course::ResourceMap& buildCost,
                           const Course::ResourceMap& production)
    : BuildingBase(eventHandler,
                   objectManager,
                   owner,
                   tileSpaces,
                   buildCost,
                   production) {

    objectManager_ = objectManager;
    setDescription("basic", "This is your base, defend it to the last man!");

}

std::string Headquarters::getType() const {

    return "Headquarters";

}

void Headquarters::onBuildAction() {

    std::vector< std::shared_ptr<Course::TileBase> > neighbours =
            objectManager_->getTiles(getCoordinatePtr()->neighbours(2));

    for(auto it = neighbours.begin(); it != neighbours.end(); ++it) {

        // If the Tile doesn't have owner, set it's owner to buildings owner.
        if( not (*it)->getOwner() )
        {
            (*it)->setOwner(getOwner());
        }

    }

}

int Headquarters::getHitPoints() {

    return hitPoints_;

}

void Headquarters::setHitPoints(int hitPoints) {

    hitPoints_ = hitPoints;

}

void Headquarters::changeHitPoints(int amount) {

    hitPoints_ = hitPoints_ + amount;

}

} // namespace Aeta
