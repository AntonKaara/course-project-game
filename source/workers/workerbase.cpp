#include "workerbase.h"

namespace Course {

WorkerBase::WorkerBase(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<BGBase::PlayerBase>& owner,
        const BGBase::Description_map& descriptions,
        const std::shared_ptr<TileBase>& tile):
    PlaceableGameObject(eventhandler, owner, descriptions, tile),
    m_resource_focus(NONE)
{
}

void WorkerBase::switchResourceFocus(BasicResource target)
{
    m_resource_focus = target;
}

BasicResource WorkerBase::getResourceFocus() const
{
    return m_resource_focus;
}

}
