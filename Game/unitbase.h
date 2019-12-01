#ifndef UNITBASE_H
#define UNITBASE_H

#include "workers/workerbase.h"

#include <QObject>
#include <string>

namespace Aeta {

class UnitBase : public Course::WorkerBase {

public:

    /**
     * @brief UnitBase Constructor for the class.
     * @param eventhandler Shared pointer to GameEventHandler.
     * @param objectmanager Shared pointer to ObjectManager.
     * @param owner Shared pointer to the unit's owner.
     * @param tilespaces Integer to define the unit's required space on a tile.
     * @param cost ResourceMap which defines the recruitment cost of the unit.
     * @param efficiency ResourceMapDouble which defines the upkeep (cost/turn)
     * of the unit.
     * @param name Unit's default name. Changed in each derived unit class.
     */
    UnitBase(const std::shared_ptr<Course::iGameEventHandler > &eventhandler,
             const std::shared_ptr<Course::iObjectManager > &objectmanager,
             const std::shared_ptr<Course::PlayerBase > &owner,
             const int &tilespaces=1, const Course::ResourceMap &cost={},
             const Course::ResourceMapDouble &efficiency={},
             const std::string &name = "Unit");

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief doSpecialAction Method for any special
     * actions of the unit. Overridden in each derived class if
     * needed.
     */
    virtual void doSpecialAction() override;

    /**
     * @brief attackUnit Attack the specified unit.
     * @param unitUnderAttack Unit to attack.
     * @return True if enemy is dead, false if the enemy is still alive
     * after the attack.
     */
    virtual bool attackUnit(std::shared_ptr<UnitBase> unitUnderAttack);

    /**
     * @brief canBePlacedOnTile Checks if the unit can be moved to the
     * specified tile. Overridden to allow unit moving on other player's
     * tiles.
     * @param tile Tile to move to.
     * @return True
     */
    bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &tile) const override;

    /**
     * @brief setName Changes the unit's display name.
     * @param name Unit's display name.
     */
    virtual void setName(const std::string name);

    /**
     * @brief setHealth Changes the unit's health to a specified amount.
     * @param amount Health amount to change to.
     */
    virtual void setHealth(const int amount);

    /**
     * @brief setMovement Changes the unit's movement points to a
     * specified amount.
     * @param amount Movement amount to change to.
     */
    virtual void setMovement(const int amount);

    /**
     * @brief setRange Changes the unit's attack range.
     * @param amount Attack range to change to.
     */
    virtual void setRange(const int amount);

    /**
     * @brief setDamage Changes the unit's damage done per attack.
     * @param amount Damage amount to change to.
     */
    virtual void setDamage(const int amount);

    /**
     * @brief getName Returns the unit's display name.
     */
    virtual std::string getName();

    /**
     * @brief getHealth Returns the unit's health amount.
     */
    virtual int getHealth();

    /**
     * @brief getMovement Returns the unit's movement points.
     */
    virtual int getMovement();

    /**
     * @brief getRange Returns the unit's attack range.
     */
    virtual int getRange();

    /**
     * @brief getDamage Returns the unit's damage per attack.
     */
    virtual int getDamage();

    /**
     * @brief getMaxHealth Returns the unit's maximum health.
     */
    virtual int getMaxHealth();

    /**
     * @brief changeHealth Changes the unit's health by a specified
     * amount.
     * @param amount Health point amount to change.
     */
    virtual void changeHealth(int amount);

    /**
     * @brief changeMovement Changes the unit's movement points by
     * a specified amount.
     * @param amount Movement point amount to change.
     */
    virtual void changeMovement(int amount);

    /**
     * @brief resetMovement Resets the unit's movement to maximum
     * amount.
     */
    virtual void resetMovement();

    Course::ResourceMapDouble UPKEEP;

protected:

    std::string unitName_ = "Unit";
    int healthPoints_ = 100;
    int maxHealthPoints_ = 100;
    int movementPoints_ = 20;
    int range_ = 1;
    int damage_ = 60;

};

} // namespace Aeta

#endif // UNITBASE_H
