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

Course::ResourceMapDouble Player::getResourcesDouble() {

    Course::ResourceMapDouble newMap;

    for (auto item : resourceAmounts_) {

        newMap.insert({item.first, static_cast<double>(item.second)});

    }

    return newMap;

}

void Player::setResources(Course::ResourceMap map) {

    resourceAmounts_ = map;

}

void Player::setResourcesDouble(Course::ResourceMapDouble map) {

    Course::ResourceMap newMap;

    for (auto item : map) {

        newMap.insert({item.first, static_cast<int>(item.second)});

    }

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
