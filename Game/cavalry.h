#include "unitbase.h"


#ifndef CAVALRY_H
#define CAVALRY_H

namespace Aeta {

class Cavalry : public UnitBase {
public:

    Cavalry(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
            const std::shared_ptr<Course::iObjectManager> &objectmanager,
            const std::shared_ptr<Course::PlayerBase> &owner, const int &tilespaces,
            const Course::ResourceMap &cost,
            const Course::ResourceMapDouble &efficiency);

    virtual std::string getType() const override;
    virtual void resetMovement() override;

};

} // namespace Aeta

#endif // CAVALRY_H
