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

const Course::ResourceMapDouble PLAYER_STARTING_RESOURCES = {
    {Course::BasicResource::MONEY, 10},
    {Course::BasicResource::FOOD, 10},
    {Course::BasicResource::WOOD, 10},

};

}

#endif // RESOURCES_HH
