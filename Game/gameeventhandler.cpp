#include "gameeventhandler.hh"

#include <QDebug>

namespace Aeta {

GameEventHandler::GameEventHandler() : Course::iGameEventHandler() {

}

bool GameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource, int amount) {

    std::shared_ptr<Player> playerCast = std::dynamic_pointer_cast<Player>(player);
    Course::ResourceMap secondMap = {};
    secondMap.insert({resource, amount});

    Course::ResourceMap newMap = Course::mergeResourceMaps(playerCast->getResources(), secondMap);

    playerCast->setResources(newMap);

    return true;
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                       Course::ResourceMap resources) {

    std::shared_ptr<Player> playerCast = std::dynamic_pointer_cast<Player>(player);
    Course::ResourceMap reduceMap = {};
    for (auto pair : resources) {
        pair.second = pair.second;
        reduceMap.insert(pair);
    }

    Course::ResourceMap newMap = Course::mergeResourceMaps(playerCast->getResources(), reduceMap);

    playerCast->setResources(newMap);

    return true;
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMapDouble resources) {

    std::shared_ptr<Player> playerCast = std::dynamic_pointer_cast<Player>(player);
    Course::ResourceMapDouble reduceMap = {};
    for (auto pair : resources) {
        pair.second = pair.second;
        reduceMap.insert(pair);

    }

    Course::ResourceMapDouble newMap = Course::mergeResourceMapDoubles(playerCast->getResourcesDouble(), reduceMap);

    playerCast->setResourcesDouble(newMap);

    return true;

}


} // namespace Aeta
