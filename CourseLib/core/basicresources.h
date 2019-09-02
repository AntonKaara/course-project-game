#ifndef BASICRESOURCES_H
#define BASICRESOURCES_H

#include <map>
namespace Course {

enum BasicResource {
    NONE = 0,
    MONEY = 1,
    FOOD = 2,
    WOOD = 3,
    STONE = 4,
    ORE = 5,
};

using ResourceMap = std::map<BasicResource, int>;
using ResourceMapDouble = std::map<BasicResource, double>;

}

#endif // BASICRESOURCES_H
