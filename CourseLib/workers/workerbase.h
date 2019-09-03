#ifndef WORKERBASE_H
#define WORKERBASE_H

#include "core/placeablegameobject.h"
#include "core/basicresources.h"


namespace Course {

/**
 * @brief The WorkerBase class is an abstract base-class for Worker-objects.
 *
 * * Workers can perform actions
 * * Tiles request production-multipliers from Workers
 */
class WorkerBase : public PlaceableGameObject
{
public:

    static const ResourceMapDouble WORKER_EFFICIENCY;
    static const ResourceMap RECRUITMENT_COST;
    /**
     * @brief Disabled default constructor.
     */
    WorkerBase() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param descriptions contains descriptions and flavor texts.
     * @param tile points to the tile upon which the building is constructed.
     */
    WorkerBase(const std::shared_ptr<iGameEventHandler>& eventhandler,
               const std::shared_ptr<iObjectManager>& objectmanager,
               const std::shared_ptr<PlayerBase>& owner,
               const int& tilespaces = 1
               );

    /**
     * @brief Default destructor.
     */
    virtual ~WorkerBase() = default;

    /**
     * @brief Performs worker's action when working a Tile for resources.
     * @return Returns the final working efficiency of a worker.
     * @note This is called by a Tile when it generates resources.
     */
    virtual const ResourceMapDouble tileWorkAction() = 0;

    /**
     * @brief Performs the Worker's special action. (If any)
     *
     * @note Hint: You can use game-eventhandler for more creative solutions.
     */
    virtual void doSpecialAction() = 0;

    /**
     * @brief Sets new resourcetype for the worker to focus on.
     * @param new_focus the new resource focus.
     * @post Exception guarantee: No-throw
     */
    virtual void setResourceFocus(BasicResource new_focus) final;

    /**
     * @brief Returns the currently focused resourcetype.
     */
    virtual BasicResource getResourceFocus() const final;
    
    /**
     * @brief Default placement rule for workers:\n
     * * Tile must have space for the worker
     * * Tile must have same owner as the worker
     * @param target is the Tile that worker is being placed on.
     * @return
     * True - Only if both conditions are met.
     * @post Exception guarantee: No-throw
     * @note
     * Override to change placement rules for derived worker.
     */
    virtual bool canBePlacedOnTile(const std::shared_ptr<TileBase> &target) const;

    /**
     * @copydoc GameObject::getType()
     */
    static std::string getType();

private:
    BasicResource m_resource_focus;


}; // class WorkerBase

} // namespace Course


#endif // WORKERBASE_H
