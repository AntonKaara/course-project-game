#ifndef BASICWORKER_H
#define BASICWORKER_H

#include "workerbase.h"

namespace Course {

/**
 * @brief The BasicWorker class represents "normal worker" in the game.
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
 *
 *
 */
class BasicWorker : public WorkerBase
{
public:
    /**
     * @brief Default constructor is disabled.
     */
    BasicWorker() = delete;

    /**
     * @brief Constructor for the class
     */
    BasicWorker(std::weak_ptr<iGameEventHandler> eventhandler,
                std::shared_ptr<BGBase::PlayerBase> owner,
                BGBase::Description_map descriptions = {});

    /**
     * @brief Default destructor
     */
    virtual ~BasicWorker() = default;

    /**
     * @copydoc BGBase::GameObject::getType()
     */
    virtual std::string getType() const override;

};

}
#endif // BASICWORKER_H
