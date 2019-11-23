#include "archery.h"

namespace Aeta {

Archery::Archery(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                 const std::shared_ptr<Course::iObjectManager> &objectmanager,
                 const std::shared_ptr<Course::PlayerBase> &owner, const int &tilespaces,
                 const Course::ResourceMap &cost,
                 const Course::ResourceMapDouble &efficiency)
    : UnitBase(eventhandler,
               objectmanager,
               owner,
               tilespaces,
               cost,
               efficiency){

    unitName_ = "Archers";
    healthPoints_ = 60;
    maxHealthPoints_ = 60;
    movementPoints_ = 3;
    range_ = 2;
    damage_ = 28;

}

std::string Archery::getType() const {

    return "Archery";

}

void Archery::resetMovement() {

    movementPoints_ = 3;

}

} // namespace Aeta
