#include "player.hh"
#include "resources.hh"



namespace Aeta {

Player::Player(const std::string& name,
               const std::vector<std::shared_ptr<Course::GameObject>> objects)
    : Course::PlayerBase(name, objects) {

    resourceAmounts_ = PLAYER_STARTING_RESOURCES;

}

Course::ResourceMap Player::getResources() {

    Course::ResourceMap intMap = {};

    for (auto item : resourceAmounts_) {

        intMap.insert({item.first, static_cast<int>(item.second)});

    }

    return intMap;

}

Course::ResourceMapDouble Player::getResourcesDouble() {

    return resourceAmounts_;

}

void Player::setResources(Course::ResourceMap map) {

    Course::ResourceMapDouble newMap = {};

    for (auto item : map) {

        newMap.insert({item.first, static_cast<double>(item.second)});

    }

    resourceAmounts_ = newMap;

}

void Player::setResources(Course::ResourceMapDouble map) {

    resourceAmounts_ = map;

}

double Player::getMoney() {

    return resourceAmounts_.at(Course::BasicResource::MONEY);

}

double Player::getFood() {

    return resourceAmounts_.at(Course::BasicResource::FOOD);

}

double Player::getWood() {

    return resourceAmounts_.at(Course::BasicResource::WOOD);

}

double Player::getStone() {

    return resourceAmounts_.at(Course::BasicResource::STONE);

}

double Player::getOre() {

    return resourceAmounts_.at(Course::BasicResource::ORE);

}


} // namespace Aeta
