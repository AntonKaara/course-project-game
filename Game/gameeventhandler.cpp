#include "gameeventhandler.hh"

namespace Aeta {

GameEventHandler::GameEventHandler() : Course::iGameEventHandler() {

}

bool GameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource, int amount) {

}

bool GameEventHandler::modifyResources(
        std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMap resources) {

}

} // namespace Aeta
