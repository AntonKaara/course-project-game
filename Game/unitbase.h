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

    void doSpecialAction() override;

};

} // namespace Aeta

#endif // UNITBASE_H
