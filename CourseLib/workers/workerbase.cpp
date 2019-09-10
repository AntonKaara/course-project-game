#include "workerbase.h"
#include "tiles/tilebase.h"


namespace Course {

WorkerBase::WorkerBase(const std::shared_ptr<iGameEventHandler>& eventhandler,
                       const std::shared_ptr<iObjectManager>& objectmanager,
                       const std::shared_ptr<PlayerBase>& owner,
                       const int& tilespaces):
    PlaceableGameObject(eventhandler, objectmanager, owner, tilespaces),
    m_resource_focus(NONE)
{
}

std::string WorkerBase::getType() const
{
    return "WorkerBase";
}

void WorkerBase::setResourceFocus(BasicResource new_focus)
{
    m_resource_focus = new_focus;
}

BasicResource WorkerBase::getResourceFocus() const
{
    return m_resource_focus;
}

bool WorkerBase::canBePlacedOnTile(const std::shared_ptr<TileBase>& target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForWorkers(spacesInTileCapacity());
}

} // namespace Course
