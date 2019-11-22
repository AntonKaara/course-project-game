#include "interfaces/igameeventhandler.h"
#include "core/playerbase.h"
#include "core/basicresources.h"
#include "core/resourcemaps.h"
#include "player.hh"


#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

namespace Aeta {

class GameEventHandler : public Course::iGameEventHandler {

public:

    GameEventHandler();

    ~GameEventHandler() override = default;

    bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                        Course::BasicResource resource, int amount) override;
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                             Course::ResourceMap resources) override;
    bool addResources(std::shared_ptr<Course::PlayerBase> player,
                         Course::ResourceMap resources);
    bool substractResources(std::shared_ptr<Course::PlayerBase> player,
                         Course::ResourceMap resources);

};

} // namespace Aeta

#endif // GAMEEVENTHANDLER_HH
