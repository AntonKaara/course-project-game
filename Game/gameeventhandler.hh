#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include "interfaces/igameeventhandler.h"
#include "core/playerbase.h"
#include "core/basicresources.h"
#include "core/resourcemaps.h"
#include "player.hh"

namespace Aeta {

class GameEventHandler : public Course::iGameEventHandler {

public:

    GameEventHandler();

    ~GameEventHandler() override = default;

    bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                        Course::BasicResource resource, int amount) override;
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                         Course::ResourceMap resources) override;
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                         Course::ResourceMapDouble resources);

};

} // namespace Aeta

#endif // GAMEEVENTHANDLER_HH
