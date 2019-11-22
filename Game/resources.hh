#include "core/basicresources.h"

#include <map>
#include <QPixmap>
#include <string>

#ifndef RESOURCES_HH
#define RESOURCES_HH

namespace Aeta {

//enum BasicResource {
//    NONE = 0,
//    MONEY = 1,
//    FOOD = 2,
//    WOOD = 3,
//    STONE = 4,
//    ORE = 5,
//    WORKFORCE = 6
//};

const Course::ResourceMap PLAYER_STARTING_RESOURCES = {

    {Course::BasicResource::MONEY, 50},
    {Course::BasicResource::FOOD, 5},
    {Course::BasicResource::WOOD, 10},
    {Course::BasicResource::STONE, 5},
    {Course::BasicResource::ORE, 0}};

}

#endif // RESOURCES_HH
