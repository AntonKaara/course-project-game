#include "player.hh"
#include "resources.hh"



namespace Aeta {

Player::Player(const std::string& name,
               const std::vector<std::shared_ptr<Course::GameObject>> objects)
    : Course::PlayerBase(name, objects) {

    resourceAmounts_ = PLAYER_STARTING_RESOURCES;

}


} // namespace Aeta
