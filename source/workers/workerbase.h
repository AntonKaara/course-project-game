#ifndef WORKERBASE_H
#define WORKERBASE_H

#include "../placeablegameobject.h"

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
    // Disable default constructor.
    WorkerBase() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler is a weak-pointer to the GameEventHandler it's going
     * to communicate with.
     * @param owner is a weak-pointer to it's owner.
     * @param descriptions is a map of strings referring to strings that
     * contain text that the user might want to store.
     */
    WorkerBase(const std::shared_ptr<iGameEventHandler>& eventhandler,
               const std::shared_ptr<BGBase::PlayerBase>& owner,
               const BGBase::Description_map& descriptions = {},
               const std::shared_ptr<TileBase>& tile = {}
               );

    /**
     * @brief Default destructor.
     */
    virtual ~WorkerBase() = default;

    /**
     * @brief Performs the Worker's default action.
     */
    virtual void doAction() = 0;

    /**
     * @brief Switch workers focus to some resource
     * @param target the newly focused resource
     * @post Exception guarantee: No throw
     */
    virtual void switchResourceFocus(BasicResource target) final;

    /**
     * @brief Get the resource-type the worker is currently focusing
     * @return Focused resource-type
     * @post Exception guarantee: No throw
     */
    virtual BasicResource getResourceFocus() const final;

    /**
     * @brief Returns the worker's multiplier for the requested resource.
     * @return The multiplier-value
     */
    virtual double getMultiplier() const = 0;

    /**
     * @copydoc BGBase::GameObject::getType()
     */
    virtual std::string getType() const = 0;

private:
    BasicResource m_resource_focus;
};

}

#endif // WORKERBASE_H
