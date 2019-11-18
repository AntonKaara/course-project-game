#include "player.hh"
#include "resources.hh"



namespace Aeta {

Player::Player(const std::string& name,
               const std::vector<std::shared_ptr<Course::GameObject>> objects,
               const uint id)
    : Course::PlayerBase(name, objects) {

    resourceAmounts_ = PLAYER_STARTING_RESOURCES;
    id_ = id;

}

uint Player::getID() {

    return id_;

}

} // namespace Aeta
