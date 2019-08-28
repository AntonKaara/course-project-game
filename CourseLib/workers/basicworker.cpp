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
                         const std::shared_ptr<PlayerBase>& owner
                         ):
    WorkerBase(eventhandler, objectmanager, owner)
{
}

std::string BasicWorker::getType() const
{
    return "BasicWorker";
}

double BasicWorker::getMultiplier() const
{
    return BASIC_PRODUCTION.at(getResourceFocus());
}

void BasicWorker::doAction()
{
    auto player = getOwner();
    auto events = lockEventHandler();
    if (events->modifyResource(player, BasicResource::FOOD, -1))
    {
        // TODO: Action
        if (events->modifyResource(player, BasicResource::MONEY, -1))
        {
            // TODO: 50 % efficiency
        }
    }
}

} // namespace Course
