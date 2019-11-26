#include "gameeventhandler.hh"

#include <QDebug>

namespace Aeta {

GameEventHandler::GameEventHandler() : Course::iGameEventHandler() {

}

bool GameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource, int amount) {

    std::shared_ptr<Player> playerCast =
            std::dynamic_pointer_cast<Player>(player);
    Course::ResourceMap map = {};
    map.insert({resource, amount});

    Course::ResourceMap newMap = Course::mergeResourceMaps(
                playerCast->getResources(), map);

    // check if some of the resources are negative and change them to zero

    for (auto resource : newMap) {

        if (resource.second < 0) {
            newMap.at(resource.first) = 0;
        }
    }

    playerCast->setResources(newMap);

    return true;
}

bool GameEventHandler::modifyResources(
        std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMap resources) {

    std::shared_ptr<Player> playerCast = std::dynamic_pointer_cast<Player>(player);

    Course::ResourceMap newMap = Course::mergeResourceMaps(
                playerCast->getResources(), resources);

    // check if some of the resources are negative and change them to zero

    for (auto resource : newMap) {

        if (resource.second < 0) {
            newMap.at(resource.first) = 0;
        }
    }

    playerCast->setResources(newMap);

    return true;
}

bool GameEventHandler::modifyResources(
        std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMapDouble resources) {

    std::shared_ptr<Player> playerCast = std::dynamic_pointer_cast<Player>(player);

    Course::ResourceMapDouble newMap = Course::mergeResourceMapDoubles(playerCast->getResourcesDouble(), resources);

    // check if some of the resources are negative and change them to zero

    for (auto resource : newMap) {

        if (resource.second < 0) {
            newMap.at(resource.first) = 0;
        }
    }

    playerCast->setResources(newMap);

    return true;

}


} // namespace Aeta
