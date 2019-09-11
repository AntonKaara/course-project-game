#include "tilebase.h"

#include <QtGlobal> // For Q_ASSERT

#include "exceptions/notenoughspace.h"
#include "exceptions/ownerconflict.h"
#include "exceptions/invalidpointer.h"
#include "core/playerbase.h"


namespace Course {

TileBase::TileBase(const Coordinate& location,
                   const std::shared_ptr<iGameEventHandler> &eventhandler,
                   const std::shared_ptr<iObjectManager>& objectmanager,
                   const unsigned int& max_build,
                   const unsigned int& max_work,
                   const ResourceMap& production):
    GameObject(location, eventhandler, objectmanager),
    MAX_BUILDINGS(max_build),
    MAX_WORKERS(max_work),
    BASE_PRODUCTION(production)
{
}

std::string TileBase::getType() const
{
    return "TileBase";
}

void TileBase::addBuilding(const std::shared_ptr<BuildingBase>& building)
{
    std::shared_ptr<TileBase> tile;
    tile = lockObjectManager()->getTile(ID);
    if (not tile)
    {
        throw InvalidPointer("Objectmanager didn't find ID: " +
                             std::to_string(ID));
    }

    if (not building->canBePlacedOnTile(tile))
    {
        throw OwnerConflict("Can't place Building on Tile!");
    }
    if (getBuildingCount() + building->spacesInTileCapacity() > MAX_BUILDINGS)
    {
        throw NotEnoughSpace("Tile has no more room for Buildings!");
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

    if (not worker->canBePlacedOnTile(std::make_shared<TileBase>(*this)))
    {
        throw OwnerConflict("Can't place Worker on Tile!");
    }
    if (getWorkerCount() + worker->spacesInTileCapacity() > MAX_WORKERS)
    {
        throw NotEnoughSpace("Tile has no more room for Workers!");
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


bool TileBase::hasSpaceForWorkers(int amount) const
{
    return amount + getWorkerCount() <= MAX_WORKERS;
}

bool TileBase::hasSpaceForBuildings(int amount) const
{
    return amount + getBuildingCount() <= MAX_BUILDINGS;
}

} // namespace Course
