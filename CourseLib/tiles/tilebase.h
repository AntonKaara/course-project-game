#ifndef TILEBASE_H
#define TILEBASE_H

#include <memory>
#include <vector>

#include "core/gameobject.h"
#include "core/basicresources.h"
#include "core/resourcemaps.h"
#include "buildings/buildingbase.h"
#include "interfaces/igameeventhandler.h"
#include "interfaces/iobjectmanager.h"
#include "workers/workerbase.h"


namespace Course {

/**
 * @brief The TileBase class is a base-class for different Tile-objects
 * in the game.
 *
 * Student uses this for: \n
 * 1. Generating resources. \n
 * 2. Adding workers that can modify production multipliers. \n
 * 3. Adding buildings that can modify production multipliers. \n
 *
 * Each tile has some constant base-production.
 * This is multiplied by worker and building-multipliers when
 * it's producing resources.
 *
 * @invariant Weak-pointer to GameEventHandler hasn't expired.
 */
class TileBase : public GameObject
{
public:
    const unsigned int MAX_BUILDINGS;
    const unsigned int MAX_WORKERS;
    const ResourceMap BASE_PRODUCTION;

    /**
     * @brief Disabled default constructor.
     */
    TileBase() = delete;

    /**
     * @brief Constructor for the class.
     *
     */
    TileBase(const Coordinate& location,
             const std::shared_ptr<iGameEventHandler>& eventhandler,
             const std::shared_ptr<iObjectManager>& objectmanager,
             const unsigned int& max_build = 2,
             const unsigned int& max_work = 3,
             const ResourceMap& production = {}
             );

    /**
     * @brief Default destructor.
     */
    virtual ~TileBase() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Adds a new Building-object to the tile.
     *
     * Phases: \n
     * 1. Building checks whether it can be placed on this tile. \n
     * 2. If the move is illegal, an exception is thrown. \n
     * 3. Add the Building to the m_buildings. \n
     * 4. Update the Building's location to this Tile. \n
     *
     * @param building points to the Building-object being added.
     * @post Exception guarantee: Strong
     * @exception OwnerConflict - If the tile's ownership prevents placing the
     * \b building.
     * @exception NoSpace - If the tile doesn't have enough space for
     * the \b building.
     * @note OwnerConflict depends on the Building-object's canPlaceOnTile.
     */
    virtual void addBuilding(const std::shared_ptr<BuildingBase>& building);

    /**
     * @brief Removes a Building-object from this Tile.
     *
     * Phases: \n
     * 1. Reset the Building's location to nothing. \n
     * 2. Remove the Building from m_buildings.
     *
     * @param building points to the Building-object being removed.
     * @post Exception guarantee: Strong
     */
    virtual void removeBuilding(const std::shared_ptr<BuildingBase>& building);

    /**
     * @brief Adds a new Worker-object to the tile.
     *
     * Phases: \n
     * 1. Worker checks whether it can be placed on this tile. \n
     * 2. If the move is illegal, an exception is thrown. \n
     * 3. Add the Worker to the m_workers. \n
     * 4. Update the Worker's location to this Tile.
     *
     * @param worker points to the Worker-object being added.
     * @post Exception guarantee: Strong
     * @exception OwnerConflict - If the tile's ownership prevents placing the
     * \b worker.
     * @exception NoSpace - If the tile doesn't have enough space for
     * the \b worker.
     * @note OwnerConflict depends on the Worker-object's canPlaceOnTile.
     */
    virtual void addWorker(const std::shared_ptr<WorkerBase>& worker);

    /**
     * @brief Removes a Worker-object from the this Tile.
     *
     * Phases: \n
     * 1. Reset the Worker's location to nothing. \n
     * 2. Remove the Worker from m_workers.
     *
     * @param worker points to the Worker-object being removed.
     * @post Exception guarantee: Strong
     */
    virtual void removeWorker(const std::shared_ptr<WorkerBase>& worker);

    /**
     * @brief Sends information to the EventHandler on
     * what resources were generated and to whom. \n
     * 1. Calls workers' tileWorkAction(). \n
     * 2. Calculate's Tile's production based on workers' efficiency. \n
     * 3. Calls buildings' getProduction(). \n
     * 4. Adds buildings' bonus production to final resource output.\n
     * 5. Sends information to GameEventHandler. \n
     * 6. Returns GameEventHandler's response.
     *
     * @post Exception guarantee: Basic guarantee
     */
    virtual bool generateResources();


    /**
     * @brief Returns the amount of spaces that are being taken from the
     * building-capacity.
     * @return The amount of space taken.
     */
    virtual unsigned int getBuildingCount() const final;

    /**
     * @brief Returns the amount of spaces that are being taken from the
     * worker-capacity.
     * @return The amount of space taken.
     */
    virtual unsigned int getWorkerCount() const final;

    /**
     * @brief Checks if the tile has enough space for workers.
     * @param amount Amount of workerspace wanted.
     * @note Uses getMaxWorkers()
     */
    virtual bool hasSpaceForWorkers(int amount) const final;

    /**
     * @brief Checks if the tile has enough space for buildings.
     * @param amount Amount of buildingspace wanted.
     * @note Uses getMaxBuildings()
     */
    virtual bool hasSpaceForBuildings(int amount) const final;

private:
    // Each GameObject-derived class with separate container
    // for easier handling.
    std::vector<std::weak_ptr<WorkerBase>> m_workers;
    std::vector<std::weak_ptr<BuildingBase>> m_buildings;

}; // class TileBase

} // namespace Course


#endif // TILEBASE_H
