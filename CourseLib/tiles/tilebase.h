#ifndef TILEBASE_H
#define TILEBASE_H

#include <memory>
#include <vector>

#include "core/gameobject.h"
#include "core/basicresources.h"
#include "buildings/buildingbase.h"
#include "interfaces/igameeventhandler.h"
#include "interfaces/iobjectmanager.h"
#include "workers/workerbase.h"


namespace Course {

// This is also an example on how you can create base-production maps
//  through initialization lists. :)
using ProductionMap = std::map<BasicResource, int>;
static const ProductionMap ZERO_BASE_PRODUCTION = {
    {MONEY, 0},
    {FOOD, 0},
    {WOOD, 0},
    {STONE, 0},
    {ORE, 0},
};

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
    const unsigned int MAX_BUILDINGS;       /**< Max room for buildings */
    const unsigned int MAX_WORKERS;         /**< Max room for workers */
    const ProductionMap BASE_PRODUCTION;    /**< Base productions before mods */

    /**
     * @brief Disabled default constructor.
     */
    TileBase() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     * @param base_production contains the base production amounts of resources.
     * @param descriptions contains descriptions and flavor texts.
     * @param max_buildings is the building limit on this Tile.
     * @param max_workers is the worker limit on this Tile.
     */
    TileBase(const Coordinate& location,
             const std::shared_ptr<iGameEventHandler>& eventhandler,
             const std::shared_ptr<iObjectManager>& objectmanager,
             const ProductionMap& base_production = ZERO_BASE_PRODUCTION,
             unsigned int max_buildings = 3,
             unsigned int max_workers = 6);

    /**
     * @brief Default destructor.
     */
    virtual ~TileBase() = default;

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

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
     * 1. Checks worker multipliers. \n
     * 2. Checks building multipliers. \n
     * 3. Adds building's production value. \n
     * 4. Multiplies the base + building -production value with
     * the calculated multiplier.
     *
     * @return
     * True - Resources were generated. \n
     * False - Nothing was generated.
     * @post Exception guarantee: Basic guarantee
     * @exception
     * ExpiredPointer - If any building or worker pointers have expired.
     */
    virtual bool generateResources();

    /**
     * @brief Increase the amount of resources in the production-pile.
     * @param type is the type of the Resource being added.
     * @param amount is the amount being added.
     * @note Can use negative values to decrease.
     * @post Exception guarantee: No-throw
     */
    virtual void increasePile(BasicResource type, int amount) final;

    /**
     * @brief Increase the producton-multiplier.
     * @param type is the Resource type whose multiplier is being modified.
     * @param amount is the amount being added.
     * @note Can use negative values to decrease.
     * @post Exception guarantee: No-throw
     */
    virtual void increaseMultiplier(BasicResource type, int amount) final;

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

protected:
    /**
     * @brief Clears the production multiplier and pile.
     */
    virtual void clearProduction();

private:
    // Each GameObject-derived class with separate container
    // for easier handling.
    std::vector<std::weak_ptr<WorkerBase>> m_workers;
    std::vector<std::weak_ptr<BuildingBase>> m_buildings;

    // Production multipliers represent the different percentual modification
    //  to production.
    std::map<BasicResource, double> m_resource_production_multipliers;

    // Production pile represents the values for different resource types
    //  before applying a production multiplier.
    ProductionMap m_resource_production_pile;

}; // class TileBase

} // namespace Course


#endif // TILEBASE_H
