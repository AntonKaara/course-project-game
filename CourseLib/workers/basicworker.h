#ifndef BASICWORKER_H
#define BASICWORKER_H

#include "workerbase.h"


namespace Course {

/**
 * @brief The BasicWorker class represents a "normal worker" in the game.
 *
 * Worker has following production-multipliers: \n
 * * Money - 0.25 \n
 * * Food - 1.00 \n
 * * Wood - 0.75 \n
 * * Stone - 0.50 \n
 * * Ore - 0.125 \n
 *
 * Workers consume Food and money. \n
 * * 1 Food - Or BasicWorker refuses to work. \n
 * * 1 Money - Or BasicWorker works at 50% efficiency. \n
 */
class BasicWorker : public WorkerBase
{
public:
    /**
     * @brief Disabled default constructor.
     */
    BasicWorker() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param descriptions contains descriptions and flavor texts.
     */
    BasicWorker(const std::shared_ptr<iGameEventHandler>& eventhandler,
                const std::shared_ptr<iObjectManager>& objectmanager,
                const std::shared_ptr<PlayerBase>& owner,
                const DescriptionMap& descriptions = {});

    /**
     * @brief Default destructor.
     */
    virtual ~BasicWorker() = default;

    /**
     * @copydoc GameObject::getType()
     */
    std::string getType() const override;

    /**
     * @brief Returns the worker's multiplier for the requested resource.
     * @return The multiplier-value
     */
    double getMultiplier() const override;

    /**
     * @brief Performs the Worker's default action.
     */
    void doAction() override;

}; // class BasicWorker

} // namespace Course


#endif // BASICWORKER_H
