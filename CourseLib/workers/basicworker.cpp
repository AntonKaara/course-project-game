#include "basicworker.h"
#include "interfaces/igameeventhandler.h"
#include "interfaces/iobjectmanager.h"

namespace Course {

static const std::map<BasicResource, double> BASIC_PRODUCTION = {
    {MONEY, 0.25},
    {FOOD, 1.00},
    {WOOD, 0.75},
    {STONE, 0.50},
    {ORE, 0.125},
};

BasicWorker::BasicWorker(const std::shared_ptr<iGameEventHandler>& eventhandler,
                         const std::shared_ptr<iObjectManager>& objectmanager,
                         const std::shared_ptr<PlayerBase>& owner,
                         const int& tilespaces
                         ):
    WorkerBase(eventhandler, objectmanager, owner, tilespaces)
{
}

std::string BasicWorker::getType()
{
    return "BasicWorker";
}

double BasicWorker::getMultiplier() const
{
    return BASIC_PRODUCTION.at(getResourceFocus()) * m_satisfaction;
}

bool BasicWorker::canPlaceOnTile(const std::shared_ptr<TileBase> &target) const
{
    return PlaceableGameObject::canPlaceOnTile(target) and
            target->hasSpaceForWorkers(spacesInTileCapacity());
}

void BasicWorker::doAction()
{
    auto player = getOwner();
    auto events = lockEventHandler();
    m_satisfaction = 0;
    if (events->modifyResource(player, BasicResource::FOOD, -1))
    {
        m_satisfaction = 0.5;
        if (events->modifyResource(player, BasicResource::MONEY, -1))
        {
            m_satisfaction = 1;
        }
    }
}

} // namespace Course
