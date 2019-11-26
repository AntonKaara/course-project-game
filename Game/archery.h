#ifndef ARCHERY_H
#define ARCHERY_H

#include "unitbase.h"

namespace Aeta {

class Archery : public UnitBase {

public:

    Archery(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
            const std::shared_ptr<Course::iObjectManager> &objectmanager,
            const std::shared_ptr<Course::PlayerBase> &owner, const int &tilespaces,
            const Course::ResourceMap &cost,
            const Course::ResourceMapDouble &efficiency);

    virtual std::string getType() const override;
    virtual void resetMovement() override;

};

} // namespace Aeta


#endif // ARCHERY_H
