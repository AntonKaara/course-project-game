#include "outpost.h"


namespace Course {

Outpost::Outpost(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<iObjectManager>& objectmanager,
        const std::shared_ptr<PlayerBase>& owner
        ):
    BuildingBase(eventhandler, objectmanager, owner, 1)
{
}

std::string Outpost::getType() const
{
    return "Outpost";
}

void Outpost::doAction()
{
}

} // namespace Course
