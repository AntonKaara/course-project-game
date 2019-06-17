#include "worldgenerator.h"

namespace Course {

WorldGenerator &WorldGenerator::getInstance()
{
    static WorldGenerator instance;
    return instance;
}

void WorldGenerator::generateMap(
        unsigned int size_x,
        unsigned int size_y,
        unsigned int seed,
        const std::shared_ptr<iObjectManager>& objectmanager)
{
    srand(seed);
    std::vector<std::shared_ptr<TileBase> > tiles = {};
    for(unsigned int x = 0; x < size_x; ++x)
    {
        for(unsigned int y = 0; y < size_y; ++y)
        {
            //TODO: implementation
            continue;
        }
    }

    try{
        objectmanager->addTiles(tiles);
    }
    catch (...){
        // throw exception
        return;
    }
}

}
