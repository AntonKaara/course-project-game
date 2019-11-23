#include "infantry.h"

#include <QDebug>

namespace Aeta {

Infantry::Infantry(const std::shared_ptr<Course::iGameEventHandler > &eventhandler,
                   const std::shared_ptr<Course::iObjectManager > &objectmanager,
                   const std::shared_ptr<Course::PlayerBase > &owner,
                   const int &tilespaces, const Course::ResourceMap &cost,
                   const Course::ResourceMapDouble &efficiency)
    : UnitBase(eventhandler,
                 objectmanager,
                 owner,
                 tilespaces,
                 cost,
                 efficiency) {

    unitName_ = "Infantrymen";
    healthPoints_ = 100;
    movementPoints_ = 2;
    range_ = 1;
    damage_ = 35;

}

std::string Infantry::getType() const {

    return "Infantry";

}



} // namespace Aeta
