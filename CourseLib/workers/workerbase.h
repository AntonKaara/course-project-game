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
     * @brief Returns the worker's multiplier for the requested resource.
     * @return The multiplier-value
     */
    virtual double getMultiplier() const = 0;

    virtual const ResourceMapDouble getMultiplierAsMap() const final;

    /**
     * @brief Performs the Worker's default action.
     */
    virtual void doAction() = 0;

    /**
     * @copydoc GameObject::getType()
     */
    static std::string getType();

    /**
     * @brief Switch the Worker's focus to some resource.
     * @param target is the newly focused resource.
     * @post Exception guarantee: No throw
     */
    virtual void switchResourceFocus(BasicResource target) final;

    /**
     * @brief Get the resource-type the Worker is currently focusing.
     * @return The focused resource-type.
     * @post Exception guarantee: No throw
     */
    virtual BasicResource getResourceFocus() const final;

private:
    BasicResource m_resource_focus;

}; // class WorkerBase

} // namespace Course


#endif // WORKERBASE_H
