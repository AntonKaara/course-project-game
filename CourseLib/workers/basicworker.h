#ifndef BASICWORKER_H
#define BASICWORKER_H

#include "workerbase.h"


namespace Course {

/**
 * @brief The BasicWorker class represents a "normal worker" in the game.
 *
 * Worker has following production-efficiency: \n
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
    static const ResourceMapDouble WORKER_EFFICIENCY;
    static const ResourceMap RECRUITMENT_COST;
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
                const int& tilespaces
                );

    /**
     * @brief Default destructor.
     */
    virtual ~BasicWorker() = default;

    /**
     * @copydoc GameObject::getType()
     */
    static std::string getType();

    /**
     * @brief Performs the Worker's default action.
     */
    virtual void doSpecialAction() override;

    virtual const ResourceMapDouble tileWorkAction() override;

private:

}; // class BasicWorker

} // namespace Course


#endif // BASICWORKER_H
