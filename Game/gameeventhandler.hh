#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include "interfaces/igameeventhandler.h"
#include "core/playerbase.h"
#include "core/basicresources.h"
#include "core/resourcemaps.h"
#include "player.hh"

namespace Aeta {

/**
 * @brief The GameEventHandler class calculates the player resources using the course-side class.
 */
class GameEventHandler : public Course::iGameEventHandler {

public:

    /**
     * @brief Class constructor
     */
    GameEventHandler();

    /**
     * @brief Default destructor
     **/
    ~GameEventHandler() override = default;

    /**
     * @brief Change the player's resources using the given amount
     **/
    bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                        Course::BasicResource resource, int amount) override;
    /**
     * @brief Change the player's resources using the given map
     **/
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                         Course::ResourceMap resources) override;
    /**
     * @brief Default Change the player's resources using the given map as double
     **/
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                         Course::ResourceMapDouble resources);

};

} // namespace Aeta

#endif // GAMEEVENTHANDLER_HH
