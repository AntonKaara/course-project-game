#include "tilebase.h"

#include "../../BGBase/source/exceptions/expiredpointer.h"

#include <QtGlobal> // For Q_ASSERT

namespace Course {

TileBase::TileBase(const BGBase::Coordinate &location,
                   const std::weak_ptr<iGameEventHandler>& eventhandler,
                   const std::map<BasicResource, int>& base_production,
                   const std::map<std::string, std::string>& descriptions,
                   unsigned int max_buildings,
                   unsigned int max_workers):
    BGBase::GameObject(location, {}, descriptions),
    MAX_BUILDINGS(max_buildings),
    MAX_WORKERS(max_workers),
    BASE_PRODUCTION(base_production),
    EVENTHANDLER(eventhandler)
{

}

void TileBase::addBuilding(const std::shared_ptr<BuildingBase>& )
{
}

void TileBase::addWorker(const std::shared_ptr<WorkerBase>&)
{
}

bool TileBase::generateResources()
{
    unsigned int expired_worker_count = 0;
    unsigned int expired_building_count = 0;
    bool produced_something = false;
    m_resource_production_pile = BASE_PRODUCTION;

    for(auto it = m_workers.begin(); it != m_workers.end(); ++it)
    {
        if(it->expired()){
            ++expired_worker_count;
        }
        auto worker = it->lock();
        auto r_type = worker->getResourceFocus();
        auto multiplier = worker->getMultiplier();
        increaseMultiplier(r_type, multiplier);
    }

    for(auto it = m_buildings.begin(); it != m_buildings.end(); ++it)
    {
        if(it->expired()){
            ++expired_building_count;
        }
        auto building = it->lock();


    }

    if( expired_worker_count or expired_building_count )
    {
        std::string msg = "Tile (ID: " + std::to_string(ID) + ") had " +
                std::to_string(expired_building_count) +
                " expired building-pointers and " +
                std::to_string(expired_worker_count) +
                " expired worker-pointers.";
        throw BGBase::ExpiredPointer(msg);
    }

    for(int r_type = BasicResource::NONE;
        r_type != BasicResource::END;
        ++r_type)
    {
        if(m_resource_production_multipliers.at(
                    static_cast<BasicResource>(r_type)) == 0)
        {
            continue;
        }
        else if(m_resource_production_pile.at(
                    static_cast<BasicResource>(r_type)) == 0)
        {
            continue;
        }

        produced_something = true;
    }
    return produced_something;
}

void TileBase::increasePile(BasicResource type, int amount)
{
    if(m_resource_production_pile.find(type) ==
            m_resource_production_pile.end())
    {
        m_resource_production_pile[type] = amount;
    }
    else
    {
        m_resource_production_pile[type] += amount;
    }
}

void TileBase::increaseMultiplier(BasicResource type, int amount)
{
    if(m_resource_production_multipliers.find(type) ==
            m_resource_production_multipliers.end())
    {
        m_resource_production_multipliers[type] = amount;
    }
    else
    {
        m_resource_production_multipliers[type] += amount;
    }
}

std::string TileBase::getType() const
{
    return "TileBase";
}

unsigned int TileBase::getBuildingCount() const
{
    return 0;
}

unsigned int TileBase::getWorkerCount() const
{
    return 0;
}

void TileBase::removeBuilding(const std::shared_ptr<BuildingBase>&)
{
}

void TileBase::removeWorker(const std::shared_ptr<WorkerBase>&)
{
}

std::shared_ptr<iGameEventHandler> TileBase::lockEventHandler()
{
    std::shared_ptr<iGameEventHandler> handler = EVENTHANDLER.lock();
    Q_ASSERT(handler);
    return handler;
}

void TileBase::clearProduction()
{
    m_resource_production_multipliers.clear();
    m_resource_production_pile.clear();
}


}
