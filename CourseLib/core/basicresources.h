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



ResourceMap mergeResourceMaps(const ResourceMap& left,
                              const ResourceMap& right);

ResourceMap multiplyResourceMap(const ResourceMap& resmap,
                                const ResourceMapDouble& multmap);

ResourceMapDouble mergeResourceMapDoubles(const ResourceMapDouble& left,
                                    const ResourceMapDouble& right);
}

#endif // BASICRESOURCES_H
