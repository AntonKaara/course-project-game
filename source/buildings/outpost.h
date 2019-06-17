#ifndef OUTPOST_H
#define OUTPOST_H

#include "buildingbase.h"

namespace Course {


/**
 * @brief The Outpost class represents a player's Outpost-building.
 *
 * It can be constructed on any tile that has not been claimed by any other
 * player. \n
 * Effects: Claims surrounding unclaimed tiles. \n
 * Radius: 2 tiles \n
 */
class Outpost : public BuildingBase
{
public:
    // Disable default-constructor
    Outpost() = delete;

    /**
     * @copydoc Course::BuildingBase::BuildingBase(
     *  std::weak_ptr<iGameEventHandler> eventhandler,
     *  std::shared_ptr<BGBase::PlayerBase> owner,
     *  std::weak_ptr<TileBase> target_tile = {},
     *  BGBase::Description_map descriptions = {})
     */
    explicit Outpost(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<BGBase::PlayerBase>& owner,
            const std::weak_ptr<TileBase>& target_tile
            );

    /**
     * @brief ~Outpost default destructor
     */
    virtual ~Outpost();

    /**
     * @brief doAction does nothing. Everything necessary is done in
     * constructor.
     */
    virtual void doAction() override;

    /**
     * @copydoc BGBase::GameObject::getType()
     */
    virtual std::string getType() const override;

private:
    /**
     * @copydoc Course::TileBase::m_EVENTHANDLER;
     */
    const std::weak_ptr<iGameEventHandler> m_EVENTHANDLER;

};

}
#endif // OUTPOST_H
