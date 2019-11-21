#include "cavalry.h"

namespace Aeta {

Cavalry::Cavalry(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                 const std::shared_ptr<Course::iObjectManager> &objectmanager,
                 const std::shared_ptr<Course::PlayerBase> &owner, const int &tilespaces,
                 const Course::ResourceMap &cost,
                 const Course::ResourceMapDouble &efficiency)
    : UnitBase(eventhandler,
               objectmanager,
               owner,
               tilespaces,
               cost,
               efficiency) {

}

std::string Cavalry::getType() const {

    return "Cavalry";
}

} // namespace Aeta
