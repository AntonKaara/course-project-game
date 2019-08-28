#include "workerbase.h"


namespace Course {

WorkerBase::WorkerBase(const std::shared_ptr<iGameEventHandler>& eventhandler,
                       const std::shared_ptr<iObjectManager>& objectmanager,
                       const std::shared_ptr<PlayerBase>& owner,
                       const std::shared_ptr<TileBase>& tile):
    PlaceableGameObject(eventhandler, objectmanager, owner, tile),
    m_resource_focus(NONE)
{
}

std::string WorkerBase::getType() const
{
    return "WorkerBase";
}

void WorkerBase::switchResourceFocus(BasicResource target)
{
    m_resource_focus = target;
}

BasicResource WorkerBase::getResourceFocus() const
{
    return m_resource_focus;
}

} // namespace Course
