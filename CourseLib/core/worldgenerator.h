#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include <functional>
#include <map>
#include <memory>

#include "interfaces/igameeventhandler.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"


namespace Course {

using TileConstructorPointer = std::function<std::shared_ptr<TileBase>(
    Coordinate,
    std::shared_ptr<iGameEventHandler>,
    std::shared_ptr<iObjectManager>)>;

/**
 * @brief The WorldGenerator class is a singleton for generating tiles
 * for the game.
 *
 * Students use this to create new Tile-objects that form the gameworld. \n
 * Usage:
 * 1. Use WorldGenerator::getInstance() to get a reference to the singleton.
 * 2. Call addConstructor with each Tile type you created.
 * 3. Generate the map through the reference.
 */
class WorldGenerator
{
public:
    /**
     * @brief Used to get a reference to the Singleton instance.
     * @return Reference to the Singleton instance.
     * @post Exception guarantee: No-throw
     */
    static WorldGenerator& getInstance();

    // Prevent copy and move construction and assignment.
    WorldGenerator(const WorldGenerator&) = delete;
    WorldGenerator& operator=(const WorldGenerator&) = delete;
    WorldGenerator(WorldGenerator&&) = delete;
    WorldGenerator& operator=(WorldGenerator&&) = delete;

    /**
     * @brief Register a Tile's constructor for use in map generation.
     * @note Do this only once per Tile type or they won't be equally common.
     * Use the Tile's type as the template parameter: addConstructor<Forest>();
     */
    template<typename T>
    void addConstructor();

    /**
     * @brief Generates Tile-objects and sends them to ObjectManager.
     * @param size_x is the horizontal size of the map area.
     * @param size_y is the vertical size of the map area.
     * @param seed is the seed-value used in the generation.
     * @param objectmanager points to the ObjectManager that receives the
     * generated Tiles.
     * @param eventhandler points to the student's GameEventHandler.
     * @post Exception guarantee: No-throw
     */
    void generateMap(unsigned int size_x,
                     unsigned int size_y,
                     unsigned int seed,
                     const std::shared_ptr<iObjectManager>& objectmanager,
                     const std::shared_ptr<iGameEventHandler>& eventhandler);

private:
    /**
     * @brief Default constructor.
     * @note Preregisters Forest and Grassland constructors. Since they are the
     * only ones that exist at the moment (before students create their own),
     * they are the only ones that can be registered at this time.
     */
    WorldGenerator();

    /**
     * @brief Default destructor.
     */
    ~WorldGenerator() = default;

    // For mapping constructors.
    std::map<unsigned int, TileConstructorPointer> m_constructors;

}; // class WorldGenerator

} // namespace Course


#endif // WORLDGENERATOR_H
