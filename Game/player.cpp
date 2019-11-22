#include "player.hh"
#include "resources.hh"



namespace Aeta {

Player::Player(const std::string& name,
               const std::vector<std::shared_ptr<Course::GameObject>> objects)
    : Course::PlayerBase(name, objects) {

    resourceAmounts_ = PLAYER_STARTING_RESOURCES;

}

Course::ResourceMap Player::getResources() {

    return resourceAmounts_;

}

void Player::setResources(Course::ResourceMap newMap) {

    resourceAmounts_ = newMap;

}

int Player::getMoney() {

    return resourceAmounts_.at(Course::BasicResource::MONEY);

}

int Player::getFood() {

    return resourceAmounts_.at(Course::BasicResource::FOOD);

}

int Player::getWood() {

    return resourceAmounts_.at(Course::BasicResource::WOOD);

}

int Player::getStone() {

    return resourceAmounts_.at(Course::BasicResource::STONE);

}

int Player::getOre() {

    return resourceAmounts_.at(Course::BasicResource::ORE);

}


} // namespace Aeta
