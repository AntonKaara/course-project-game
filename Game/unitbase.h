#ifndef UNITBASE_H
#define UNITBASE_H

#include "workers/workerbase.h"

#include <QObject>
#include <string>

namespace Aeta {

class UnitBase : public Course::WorkerBase {

public:

    UnitBase(const std::shared_ptr<Course::iGameEventHandler > &eventhandler,
             const std::shared_ptr<Course::iObjectManager > &objectmanager,
             const std::shared_ptr<Course::PlayerBase > &owner,
             const int &tilespaces=1, const Course::ResourceMap &cost={},
             const Course::ResourceMapDouble &efficiency={},
             const std::string &name = "Unit");

    virtual std::string getType() const override;
    virtual void doSpecialAction() override;
    virtual bool attackUnit(std::shared_ptr<UnitBase> unitUnderAttack);

    virtual void setName(const std::string name);
    virtual void setHealth(const int amount);
    virtual void setMovement(const int amount);
    virtual void setRange(const int amount);
    virtual void setDamage(const int amount);

    virtual std::string getName();
    virtual int getHealth();
    virtual int getMovement();
    virtual int getRange();
    virtual int getDamage();
    virtual int getMaxHealth();

    virtual void changeHealth(int amount);
    virtual void changeMovement(int amount);
    virtual void resetMovement();

    Course::ResourceMapDouble UPKEEP;

protected:

    std::string unitName_ = "Unit";
    int healthPoints_ = 100;
    int maxHealthPoints_ = 100;
    int movementPoints_ = 20;
    int range_ = 1;
    int damage_ = 60;

private:

};

} // namespace Aeta

#endif // UNITBASE_H
