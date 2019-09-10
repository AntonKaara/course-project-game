#include "basicworker.h"
#include "interfaces/igameeventhandler.h"
#include "interfaces/iobjectmanager.h"

namespace Course {

const ResourceMapDouble BasicWorker::WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 1.00},
    {WOOD, 0.75},
    {STONE, 0.50},
    {ORE, 0.125}
};

const ResourceMap BasicWorker::RECRUITMENT_COST = {
    {MONEY, 100},
    {FOOD, 25}
};

BasicWorker::BasicWorker(const std::shared_ptr<iGameEventHandler>& eventhandler,
                         const std::shared_ptr<iObjectManager>& objectmanager,
                         const std::shared_ptr<PlayerBase>& owner,
                         const int& tilespaces
                         ):
    WorkerBase(eventhandler, objectmanager, owner, tilespaces)
{
}

std::string BasicWorker::getType() const
{
    return "BasicWorker";
}

void BasicWorker::doSpecialAction()
{

}

const ResourceMapDouble BasicWorker::tileWorkAction()
{
    auto player = getOwner();
    auto events = lockEventHandler();
    double satisfaction = 0;
    BasicResource focus = getResourceFocus();

    ResourceMapDouble final_modifier;

    if (events->modifyResource(player, BasicResource::FOOD, -1))
    {
        satisfaction = 0.5;
        if (events->modifyResource(player, BasicResource::MONEY, -1))
        {
            satisfaction = 1;
        }
    }


    if( focus != BasicResource::NONE)
    {
        final_modifier[focus] =
                (WORKER_EFFICIENCY.at(focus) + 0.25) * satisfaction;
    }
    else
    {
        for( auto it = WORKER_EFFICIENCY.begin();
             it != WORKER_EFFICIENCY.end();
             ++it)
        {
            final_modifier[it->first] = it->second * satisfaction;
        }
    }

    return final_modifier;
}


} // namespace Course
