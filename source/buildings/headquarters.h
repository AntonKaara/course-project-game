#ifndef HEADQUARTERS_H
#define HEADQUARTERS_H

#include <memory>

#include "buildingbase.h"
#include "../../BGBase/source/playerbase.h"

namespace Course {

/**
 * @brief The HeadQuarters class represents a player's HeadQuarter-building.
 *
 * It can be constructed on any tile that has not been claimed by any other
 * player. \n
 * Effects: Claims surrounding unclaimed tiles. \n
 * Radius: 3 tiles.\n
 */
class HeadQuarters : public BuildingBase
{
public:
    HeadQuarters() = delete;

    /**
     * @copydoc Course::BuildingBase::BuildingBase(
     *  std::weak_ptr<iGameEventHandler> eventhandler,
     *  std::shared_ptr<BGBase::PlayerBase> owner,
     *  std::weak_ptr<TileBase> target_tile = {},
     *  BGBase::Description_map descriptions = {})
     */
    explicit HeadQuarters(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<BGBase::PlayerBase>& owner,
            const std::shared_ptr<TileBase>& location
            );

    /**
     * @brief ~HeadQuarters default destructor
     */
    virtual ~HeadQuarters() = default;

    /**
     * @brief doAction does nothing.
     * All the necessary actions are done in constructor.
     */
    virtual void doAction() override;

    /**
     * @copydoc BGBase::GameObject::getType()
     */
    virtual std::string getType() const override;
};

}

#endif // HEADQUARTERS_H
