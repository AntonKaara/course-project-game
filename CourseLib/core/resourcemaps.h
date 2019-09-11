#ifndef RESOURCEMAPS_H
#define RESOURCEMAPS_H

#include "basicresources.h"

namespace Course {

namespace ConstResourceMaps {

const ResourceMap EMPTY = {};

// Building - Farm
const ResourceMap FARM_BUILD_COST = {
    {BasicResource::MONEY, 250},
    {BasicResource::FOOD, 50},
    {BasicResource::WOOD, 50},
    {BasicResource::STONE, 10}
};
const ResourceMap FARM_PRODUCTION = {
    {BasicResource::FOOD, 2}
};


// Building - HeadQuarters
const ResourceMap HQ_BUILD_COST = {
    {BasicResource::MONEY, 1000},
    {BasicResource::FOOD, 500},
    {BasicResource::WOOD, 300},
    {BasicResource::STONE, 200},
    {BasicResource::ORE, 100}
};
const ResourceMap HQ_PRODUCTION = {
    {BasicResource::MONEY, 50}
};


// Building - Outpost
const ResourceMap OUTPOST_BUILD_COST = {
    {BasicResource::MONEY, 250},
    {BasicResource::FOOD, 100},
    {BasicResource::WOOD, 75},
    {BasicResource::STONE, 25}
};

const ResourceMap OUTPOST_PRODUCTION = {
    {BasicResource::MONEY, -10}
};


// Worker - BasicWorker
const ResourceMapDouble BW_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 1.00},
    {WOOD, 0.75},
    {STONE, 0.50},
    {ORE, 0.125}
};

const ResourceMap BW_RECRUITMENT_COST = {
    {MONEY, 100},
    {FOOD, 25}
};


const ResourceMap FOREST_BP = {
    {MONEY, 1},
    {FOOD, 2},
    {WOOD, 1},
    {STONE, 0},
    {ORE, 0},
};

const ResourceMap GRASSLAND_BP = {
    {MONEY, 1},
    {FOOD, 2},
    {WOOD, 1},
    {STONE, 0},
    {ORE, 0},
};


}
}
#endif // RESOURCEMAPS_H
