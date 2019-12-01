#ifndef RESOURCES_HH
#define RESOURCES_HH

#include "core/basicresources.h"

#include <map>
#include <QPixmap>
#include <string>

namespace Aeta {

// RESOURCEMAP STORAGE

const Course::ResourceMapDouble PLAYER_STARTING_RESOURCES = {

    {Course::BasicResource::MONEY, 275.0},
    {Course::BasicResource::FOOD, 50.0},
    {Course::BasicResource::WOOD, 120.0},
    {Course::BasicResource::STONE, 50.0},
    {Course::BasicResource::ORE, 2.0}

};

const Course::ResourceMap FARM_BUILD_COST = {

    {Course::BasicResource::MONEY, -30},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, -10},
    {Course::BasicResource::STONE, -5},
    {Course::BasicResource::ORE, 0}

};

const Course::ResourceMap FARM_PRODUCTION = {

    {Course::BasicResource::MONEY, 12},
    {Course::BasicResource::FOOD, 15},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}

};

const Course::ResourceMap OUTPOST_BUILD_COST = {

    {Course::BasicResource::MONEY, -65},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, -100},
    {Course::BasicResource::STONE, -45},
    {Course::BasicResource::ORE, -14}

};

const Course::ResourceMap OUTPOST_PRODUCTION = {

    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}

};

const Course::ResourceMap HQ_BUILD_COST = {

    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}

};

const Course::ResourceMap HQ_PRODUCTION = {

    {Course::BasicResource::MONEY, 75},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}

};

const Course::ResourceMap MINE_BUILD_COST = {

    {Course::BasicResource::MONEY, -20},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, -30},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}

};

const Course::ResourceMap MINE_PRODUCTION = {

    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 18},
    {Course::BasicResource::ORE, 2}

};

const Course::ResourceMap LUMBERMILL_BUILD_COST = {

    {Course::BasicResource::MONEY, -30},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, -30},
    {Course::BasicResource::STONE, -20},
    {Course::BasicResource::ORE, 0}

};

const Course::ResourceMap LUMBERMILL_PRODUCTION = {

    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 25},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}

};
const Course::ResourceMap INFANTRY_RECRUITMENT_COST = {

    {Course::BasicResource::MONEY, -200},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, -1}

};

const Course::ResourceMapDouble INFANTRY_UPKEEP = {

    {Course::BasicResource::MONEY, -10},
    {Course::BasicResource::FOOD, -10},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}

};
const Course::ResourceMap ARCHERY_RECRUITMENT_COST = {

    {Course::BasicResource::MONEY, -150},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, -10},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, -1}

};

const Course::ResourceMapDouble ARCHERY_UPKEEP = {

    {Course::BasicResource::MONEY, -10},
    {Course::BasicResource::FOOD, -5},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}

};

const Course::ResourceMap CAVALRY_RECRUITMENT_COST = {

    {Course::BasicResource::MONEY, -350},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, -5}

};

const Course::ResourceMapDouble CAVALRY_UPKEEP = {

    {Course::BasicResource::MONEY, -25},
    {Course::BasicResource::FOOD, -20},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}

};

} // namespace Aeta

#endif // RESOURCES_HH
