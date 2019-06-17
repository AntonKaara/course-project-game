#ifndef TILEBASE_H
#define TILEBASE_H

#include "../../BGBase/source/gameobject.h"
#include "../../BGBase/source/coordinate.h"
#include "../buildings/buildingbase.h"
#include "../workers/workerbase.h"
#include "../basicresources.h"
#include "../interfaces/igameeventhandler.h"

#include <map>

namespace Course {

// This is also an example on how you can create base-production maps
//  through initialization lists. :)
const std::map<BasicResource, int> ZERO_BASE_PRODUCTION = {
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
class TileBase : public BGBase::GameObject
{
public:
    const unsigned int MAX_BUILDINGS;
    const unsigned int MAX_WORKERS;
    const std::map<BasicResource, int> BASE_PRODUCTION;

    /**
     * @brief Default constructor is disabled.
     */
    TileBase()=delete;

    /**
     * @brief Default destructor.
     */
    virtual ~TileBase() = default;

    /**
     * @brief Constructor for this class
     * @param location is the BGBase::Coordinate to where the Tile
     * is located in the gameworld
     * @param eventhandler is a consant weak-pointer to the Student's
     * GameEventHandler
     */
    TileBase(const BGBase::Coordinate& location,
             const std::weak_ptr<iGameEventHandler>& eventhandler,
             const std::map<BasicResource, int>& base_production =
                ZERO_BASE_PRODUCTION,
             const std::map<std::string, std::string>& descriptions = {},
             unsigned int max_buildings = 3,
             unsigned int max_workers = 6);

    /**
     * @brief Adds a new Building-object to the tile.
     *
     * Phases: \n
     * 1. Building performs the check whether it can be placed on this tile. \n
     * 2. If the move is illegal, exception is thrown. \n
     * 3. Add the Building to the m_buildings. \n
     * 4. Update Building's location to this Tile. \n
     *
     * @param building is a pointer to the Building-object being added.
     * @post Exception guarantee: Strong
     * @exception OwnerConflict - If the tile's ownership prevents placing the
     * \b building.
     * @exception NoSpace - If the tile doesn't have enough space for
     * the \b building.
     * @note OwnerConflict depends on Building-object's can_place.
     */
    virtual void addBuilding(const std::shared_ptr<BuildingBase>& building);

    /**
     * @brief Adds a new Worker-object to the tile.
     *
     * Phases: \n
     * 1. Worker performs the check whether it can be placed on this tile. \n
     * 2. If the move is illegal, exception is thrown. \n
     * 3. Add the Worker to the m_workers. \n
     * 4. Update Worker's location to this tile. \n
     * @param worker is a pointer to the Worker-object being added.
     * @post Exception guarantee: Strong
     * @exception OwnerConflict - If the tile's ownership prevents placing
     * of the \b worker.
     */
    virtual void addWorker(const std::shared_ptr<WorkerBase>& worker);

    /**
     * @brief Sends information to the EventHandler on
     * what resources were generated and to whom. \n
     * 1. Checks worker multipliers. \n
     * 2. Checks building multipliers. \n
     * 3. Adds building's production value. \n
     * 4. Multiplies the base + building -production value with
     * the calculated multiplier \n
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
     * @brief Increase the amount of resources in production-pile.
     * @param type Resource-type being added
     * @param amount The amount being added
     * @note Can use negative values to decrease.
     * @post Exception guarantee: No-throw
     */
    virtual void increasePile(BasicResource type, int amount) final;
    /**
     * @brief Increase the producton-multiplier.
     * @param type Resource-type the multiplier is being applied to.
     * @param amount The amount being added
     * @note Can use negative values to decrease.
     * @post Exception guarantee: No-throw
     */
    virtual void increaseMultiplier(BasicResource type, int amount) final;

    /**
     * @copydoc BGBase::GameObject::getType()
     */
    virtual std::string getType() const override;

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
     * @brief Removes a Building-object from this Tile.
     *
     * Phases: \n
     * 1. Reset the Building's location to nothing. \n
     * 2. Remove the Building from m_buildings. \n
     *
     * @param building is a pointer to the Building-object being removed.
     * @post Exception guarantee: Strong
     */
    virtual void removeBuilding(const std::shared_ptr<BuildingBase>& building);

    /**
     * @brief Removes a Worker-object from the this Tile.
     *
     * Phases: \n
     * 1. Reset the Worker's location to nothing. \n
     * 2. Remove the Worker from m_workers. \n
     * @param worker is a pointer to the Worker-object being removed.
     * @post Exception guarantee: Strong
     */
    virtual void removeWorker(const std::shared_ptr<WorkerBase>& worker);

protected:
    /**
     * @brief Locks the eventhandler for use and checks the class-invariant.
     * @return Usable shared_ptr to the GameEventHandler.
     */
    virtual std::shared_ptr<iGameEventHandler> lockEventHandler() final;

    /**
     * @brief Clears the production multiplier and pile.
     */
    virtual void clearProduction();

private:

    // Each GameObject-derived class with separate container
    // for easier handling.
    std::vector<std::weak_ptr<WorkerBase> > m_workers;
    std::vector<std::weak_ptr<BuildingBase> > m_buildings;

    // Production multipliers represent the different percentual modification
    //  to production.
    std::map<BasicResource, double> m_resource_production_multipliers;

    // Production pile represents the values for different resource types
    //  before applying a production multiplier.
    std::map<BasicResource, int> m_resource_production_pile;

    const std::weak_ptr<iGameEventHandler> EVENTHANDLER;

};

}
#endif // TILEBASE_H
