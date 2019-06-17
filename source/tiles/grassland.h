#ifndef GRASSLAND_H
#define GRASSLAND_H

#include "tilebase.h"

namespace Course {

/**
 * @brief The Grassland class represents Grassland in the gameworld.
 *
 * Grassland has BasicProduction: \n
 * Money = 1 \n
 * Food = 2 \n
 * Wood = 1 \n
 * Stone = 0 \n
 * Ore = 0 \n
 *
 * Functionality follows mainly the parent class' functionality.
 *
 * Tile supports 3 buildings.
 *
 * @invariant Weak-pointer to GameEventHandler hasn't expired.
 */
class Grassland : public TileBase
{
public:
    /**
     * @brief Default constructor is disabled.
     */
    Grassland() = delete;

    /**
     * @brief Constructor for this class.
     * @param location is the BGBase::Coordinate to where the Tile is located
     * in the gameworld.
     * @param eventhandler is a consant weak-pointer to the Student's
     * GameEventHandler
     */
    Grassland(const BGBase::Coordinate& location,
              const std::shared_ptr<iGameEventHandler>& eventhandler);

    /**
     * @copydoc BGBase::GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief addBuilding
     * @param building
     */
    virtual void addBuilding(
            const std::shared_ptr<BuildingBase>& building) override;
};

}

#endif // GRASSLAND_H
