#include "tilebase.h"

#include <QtGlobal> // For Q_ASSERT

#include "exceptions/expiredpointer.h"
#include "exceptions/nospace.h"
#include "exceptions/ownerconflict.h"
#include "core/playerbase.h"


namespace Course {

TileBase::TileBase(const Coordinate& location,
                   const std::shared_ptr<iGameEventHandler> &eventhandler,
                   const std::shared_ptr<iObjectManager>& objectmanager,
                   const ProductionMap& base_production,
                   unsigned int max_buildings,
                   unsigned int max_workers):
    GameObject(location, eventhandler, objectmanager),
    MAX_BUILDINGS(max_buildings),
    MAX_WORKERS(max_workers),
    BASE_PRODUCTION(base_production)
{
}

std::string TileBase::getType() const
{
    return "TileBase";
}

void TileBase::addBuilding(const std::shared_ptr<BuildingBase>& building)
{
    std::shared_ptr<TileBase> tile;
    for (const auto& obj : getOwner()->getObjects())
    {
        if (obj.get() == this)
        {
            tile = std::dynamic_pointer_cast<TileBase>(obj);
        }
    }
    if (not tile)
    {
        // TODO: Throw? Which exception?
        //throw KeyError("");
    }

    if (not building->canPlaceOnTile(tile))
    {
        throw OwnerConflict("Can't place Building on Tile!");
    }
    if (getBuildingCount() + building->spacesInTileCapacity() > MAX_BUILDINGS)
    {
        throw NoSpace("Tile has no more room for Buildings!");
    }
    m_buildings.push_back(building);
    building->setLocationTile(tile);
}

void TileBase::removeBuilding(const std::shared_ptr<BuildingBase>& building)
{
    building->setLocationTile(nullptr);
    for (std::size_t i = 0; i < m_buildings.size(); ++i)
    {
        if (not m_buildings[i].expired() and m_buildings[i].lock() == building)
        {
            m_buildings.erase(m_buildings.begin() + i);
            return;
        }
    }
}

void TileBase::addWorker(const std::shared_ptr<WorkerBase>& worker)
{
    std::shared_ptr<TileBase> tile;
    for (const auto& obj : getOwner()->getObjects())
    {
        if (obj.get() == this)
        {
            tile = std::dynamic_pointer_cast<TileBase>(obj);
        }
    }
    if (not tile)
    {
        // TODO: Throw? Which exception?
        //throw KeyError("");
    }

    if (not worker->canPlaceOnTile(std::make_shared<TileBase>(*this)))
    {
        throw OwnerConflict("Can't place Worker on Tile!");
    }
    if (getWorkerCount() + worker->spacesInTileCapacity() > MAX_WORKERS)
    {
        throw NoSpace("Tile has no more room for Workers!");
    }
    m_workers.push_back(worker);
    worker->setLocationTile(tile);
}

void TileBase::removeWorker(const std::shared_ptr<WorkerBase>& worker)
{
    worker->setLocationTile(nullptr);
    for (std::size_t i = 0; i < m_workers.size(); ++i)
    {
        if (not m_workers[i].expired() and m_workers[i].lock() == worker)
        {
            m_workers.erase(m_workers.begin() + i);
            return;
        }
    }
}

bool TileBase::generateResources()
{
    unsigned int expired_worker_count = 0;
    unsigned int expired_building_count = 0;
    bool produced_something = false;
    m_resource_production_pile = BASE_PRODUCTION;

    for (const auto& weak_worker : m_workers)
    {
        if (weak_worker.expired())
        {
            ++expired_worker_count;
            continue;
        }
        auto worker = weak_worker.lock();
        auto r_type = worker->getResourceFocus();
        auto multiplier = worker->getMultiplier();
        increaseMultiplier(r_type, multiplier);
    }

    for (const auto& weak_building : m_buildings)
    {
        if (weak_building.expired())
        {
            ++expired_building_count;
            continue;
        }
        auto building = weak_building.lock();
        for (int br = BasicResource::NONE; br <= BasicResource::ORE; ++br)
        {
            auto r_type = static_cast<BasicResource>(br);
            increaseMultiplier(r_type, building->getMultiplier(r_type));
            increasePile(r_type, building->getProduction(r_type));
        }
    }

    if (expired_worker_count or expired_building_count)
    {
        std::string msg = "Tile (ID: " + std::to_string(ID) + ") had " +
                std::to_string(expired_building_count) +
                " expired building-pointers and " +
                std::to_string(expired_worker_count) +
                " expired worker-pointers.";
        throw ExpiredPointer(msg);
    }

    for (int br = BasicResource::NONE; br != BasicResource::ORE; ++br)
    {
        auto r_type = static_cast<BasicResource>(br);
        auto base = m_resource_production_pile.at(r_type);
        auto multiplier = m_resource_production_multipliers.at(r_type);
        auto production = static_cast<int>(base * multiplier);
        if (production)
        {
            lockEventHandler()->modifyResource(getOwner(), r_type, production);
            produced_something = true;
        }
    }

    return produced_something;
}

void TileBase::increasePile(BasicResource type, int amount)
{
    m_resource_production_pile[type] += amount;
}

void TileBase::increaseMultiplier(BasicResource type, int amount)
{
    m_resource_production_multipliers[type] += amount;
}

unsigned int TileBase::getBuildingCount() const
{
    unsigned taken = 0;
    for (const auto& bldn : m_buildings)
    {
        if (not bldn.expired())
        {
            taken += bldn.lock()->spacesInTileCapacity();
        }
    }
    return taken;
}

unsigned int TileBase::getWorkerCount() const
{
    unsigned taken = 0;
    for (const auto& wrkr : m_workers)
    {
        if (not wrkr.expired())
        {
            taken += wrkr.lock()->spacesInTileCapacity();
        }
    }
    return taken;
}

void TileBase::clearProduction()
{
    m_resource_production_multipliers.clear();
    m_resource_production_pile.clear();
}

} // namespace Course
