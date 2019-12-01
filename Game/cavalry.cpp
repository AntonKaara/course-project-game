#include "cavalry.h"

namespace Aeta {

Cavalry::Cavalry(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                 const std::shared_ptr<Course::iObjectManager> &objectmanager,
                 const std::shared_ptr<Course::PlayerBase> &owner,
                 const int &tilespaces,
                 const Course::ResourceMap &cost,
                 const Course::ResourceMapDouble &efficiency)
    : UnitBase(eventhandler,
               objectmanager,
               owner,
               tilespaces,
               cost,
               efficiency) {

    unitName_ = "Horsemen";
    healthPoints_ = 120;
    maxHealthPoints_ = 120;
    movementPoints_ = 5;
    range_ = 1;
    damage_ = 42;

}

std::string Cavalry::getType() const {

    return "Cavalry";
}

void Cavalry::resetMovement() {

    movementPoints_ = 5;

}

} // namespace Aeta
