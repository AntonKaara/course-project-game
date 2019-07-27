#include "worldgenerator.h"

#include <vector>
#include "tiles/forest.h"
#include "tiles/grassland.h"


namespace Course {

WorldGenerator& WorldGenerator::getInstance()
{
    static WorldGenerator instance;
    return instance;
}

template<typename T>
void WorldGenerator::addConstructor()
{
    TileConstructorPointer ctor = std::make_shared<T, Coordinate,
            std::shared_ptr<iGameEventHandler>,
            std::shared_ptr<iObjectManager> >;

    m_constructors[m_constructors.size()] = ctor;
}



WorldGenerator::WorldGenerator()
{
    addConstructor<Forest>();
    addConstructor<Grassland>();
}

void WorldGenerator::generateMap(
        unsigned int size_x,
        unsigned int size_y,
        unsigned int seed,
        const std::shared_ptr<iObjectManager>& objectmanager,
        const std::shared_ptr<iGameEventHandler>& eventhandler)
{
    srand(seed);
    std::vector<std::shared_ptr<TileBase>> tiles;
    for (unsigned int x = 0; x < size_x; ++x)
    {
        for (unsigned int y = 0; y < size_y; ++y)
        {
            auto ctor = m_constructors[rand() % m_constructors.size()];
            tiles.push_back(ctor(Coordinate(x, y), eventhandler, objectmanager));
        }
    }

    objectmanager->addTiles(tiles);
}

} // namespace Course
