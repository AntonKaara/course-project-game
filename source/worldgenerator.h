#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include <vector>
#include <string>
#include <functional>
#include <map>

#include "tiles/tilebase.h"
#include "interfaces/iobjectmanager.h"

namespace Course {

using TileConstructorPointer =
    std::function<std::shared_ptr<TileBase>(BGBase::Coordinate)>;

/**
 * @brief The WorldGenerator class is a singleton for generating tiles
 * for the game.
 *
 * Student's use this to create new Tile-objects that form the gameworld. \n
 * Usage: \n
 * 1. Use WorldGenerator::getInstance() to get pointer to the singleton. \n
 * 2. Generate the map through the pointer. \n
 */
class WorldGenerator
{
public:
    /**
     * @brief Used to get reference to the Singleton instance.
     * @return Reference to the Singleton instance.
     * @post Exception guarantee: No-throw
     */
    static WorldGenerator& getInstance();
    /**
     * @brief Default destructor
     */
    ~WorldGenerator();

    /**
     * @brief Generates Tile-objects and sends them to ObjectManager.
     * @param size_x is the horizontal size of the map area.
     * @param size_y is the vertical size of the map area.
     * @param seed is the seed-value used in the generation.
     * @param objectmanager is a shared-pointer to ObjectManager that receives
     * the generated Tiles.
     * @post Exception guarantee: No-throw
     */
    void generateMap(unsigned int size_x,
                     unsigned int size_y,
                     unsigned int seed,
                     const std::shared_ptr<iObjectManager>& objectmanager);

    // Prevent copy-construction and assignment.
    WorldGenerator(WorldGenerator const&) = delete;
    void operator=(WorldGenerator const&) = delete;

private:
    WorldGenerator() = default;
    static WorldGenerator* INSTANCE;

    // For mapping constructors.
    std::map<unsigned int, TileConstructorPointer> m_constructors;

    // Create constructor pointers
    void createTileConstructorMap();

    // Calls tile constructors
    std::shared_ptr<TileBase> createTile(unsigned int type);
};

}
#endif // WORLDGENERATOR_H
