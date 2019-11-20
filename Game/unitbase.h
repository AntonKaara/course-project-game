#include "workers/workerbase.h"

#include <QObject>

#ifndef UNITBASE_H
#define UNITBASE_H

namespace Aeta {

class UnitBase : public Course::WorkerBase {

public:

    UnitBase(const std::shared_ptr<Course::iGameEventHandler > &eventhandler,
             const std::shared_ptr<Course::iObjectManager > &objectmanager,
             const std::shared_ptr<Course::PlayerBase > &owner,
             const int &tilespaces=1, const Course::ResourceMap &cost={},
             const Course::ResourceMapDouble &efficiency={});

    virtual std::string getType() const override;
    virtual void doSpecialAction() override;

    virtual void setName(const std::string name);
    virtual void setHealth(const int amount);
    virtual void setMovement(const double amount);
    virtual void setRange(const int amount);
    virtual void setDamage(const int amount);

    virtual std::string getName();
    virtual int getHealth();
    virtual double getMovement();
    virtual int getRange();
    virtual int getDamage();

    virtual void changeHealth(int amount);
    virtual void changeMovement(int amount);


private:

    std::string unitName_;
    int healthPoints_;
    double movementPoints_;
    int range_;
    int damage_;


};

} // namespace Aeta

#endif // UNITBASE_H
