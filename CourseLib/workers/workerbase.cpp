#include "workerbase.h"


namespace Course {

WorkerBase::WorkerBase(const std::shared_ptr<iGameEventHandler>& eventhandler,
                       const std::shared_ptr<iObjectManager>& objectmanager,
                       const std::shared_ptr<PlayerBase>& owner,
                       const int& tilespaces):
    PlaceableGameObject(eventhandler, objectmanager, owner, tilespaces),
    m_resource_focus(NONE)
{
}

const ResourceMapDouble WorkerBase::getMultiplierAsMap() const
{
    return ResourceMapDouble({{getResourceFocus(), getMultiplier()}});
}

std::string WorkerBase::getType()
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
