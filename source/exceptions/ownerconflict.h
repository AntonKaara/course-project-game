#ifndef OWNERCONFLICT_H
#define OWNERCONFLICT_H

#include "../BGBase/source/exceptions/baseexception.h"

namespace Course {

/**
 * @brief The OwnerConflict class is an Exception-class for cases where an
 * operation is conflicting with GameObject's ownership.
 */
class OwnerConflict : public BGBase::BaseException
{
public:
    /**
     * @copydoc BGBase::BaseException::BaseException
     */
    explicit OwnerConflict(const std::string& msg = ""):
        BGBase::BaseException(msg);

    virtual ~OwnerConflict() = default;

};

}
#endif // OWNERCONFLICT_H
