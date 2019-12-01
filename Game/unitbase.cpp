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
    unitName_ = name;
    UPKEEP = efficiency;
}

std::string UnitBase::getType() const {
    return "Generic unit";
}

void UnitBase::doSpecialAction() {

}

bool UnitBase::attackUnit(std::shared_ptr<UnitBase> unitUnderAttack) {

    unitUnderAttack->changeHealth(-damage_);

    // return true if enemy died, false otherwise

    if (unitUnderAttack->getHealth() <= 0) {
        return true;
    } else {
        return false;
    }

}

bool UnitBase::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &tile) const {
    return true;
}

void UnitBase::setName(const std::string name) {
    unitName_ = name;
}

void UnitBase::setHealth(const int amount) {
    healthPoints_ = amount;
}

void UnitBase::setMovement(const int amount) {
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

int UnitBase::getMovement() {
    return movementPoints_;
}

int UnitBase::getRange() {
    return range_;
}

int UnitBase::getDamage() {
    return damage_;
}

int UnitBase::getMaxHealth() {
    return maxHealthPoints_;
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
