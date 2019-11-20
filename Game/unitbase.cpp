#include "unitbase.h"

namespace Aeta {

UnitBase::UnitBase(const std::shared_ptr<Course::iGameEventHandler > &eventhandler,
                   const std::shared_ptr<Course::iObjectManager > &objectmanager,
                   const std::shared_ptr<Course::PlayerBase > &owner,
                   const int &tilespaces, const Course::ResourceMap &cost,
                   const Course::ResourceMapDouble &efficiency,
                   const std::string &name)
    : WorkerBase(eventhandler,
                 objectmanager,
                 owner,
                 tilespaces,
                 cost,
                 efficiency)  {


}

std::string UnitBase::getType() const {
    return "Generic unit"; // Override in child classes
}

void UnitBase::doSpecialAction() {
    // Override in child classes
}

void UnitBase::setName(const std::string name) {
    unitName_ = name;
}

void UnitBase::setHealth(const int amount) {
    healthPoints_ = amount;
}

void UnitBase::setMovement(const double amount) {
    movementPoints_ = amount;
}

void UnitBase::setRange(const int amount) {
    range_ = amount;
}

void UnitBase::setDamage(const int amount) {
    damage_ = amount;
}

std::string UnitBase::getName() {
    return unitName_;
}

int UnitBase::getHealth() {
    return healthPoints_;
}

double UnitBase::getMovement() {
    return movementPoints_;
}

int UnitBase::getRange() {
    return range_;
}

int UnitBase::getDamage() {
    return damage_;
}

void UnitBase::changeHealth(int amount) {
    healthPoints_ =  healthPoints_ + amount;
}

void UnitBase::changeMovement(int amount) {
    movementPoints_ = movementPoints_ + amount;
}

void UnitBase::resetMovement() {
    movementPoints_ = 2;
}

} // namespace Aeta
