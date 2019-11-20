#include "unitbase.h"

#ifndef INFANTRY_H
#define INFANTRY_H

namespace Aeta {

class Infantry : public UnitBase {

public:

    Infantry(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
             const std::shared_ptr<Course::iObjectManager> &objectmanager,
             const std::shared_ptr<Course::PlayerBase> &owner, const int &tilespaces,
             const Course::ResourceMap &cost,
             const Course::ResourceMapDouble &efficiency);

    std::string getType() const override;

};

} // namespace Aeta

#endif // INFANTRY_H
