#ifndef EXPIREDPOINTER_H
#define EXPIREDPOINTER_H

#include "baseexception.h"

namespace Course {

/**
 * @brief The ExpiredPointer class is a Exception class for errors when
 * used weak-pointer couldn't be locked.
 */
class ExpiredPointer : public BaseException
{
public:
    /**
     * @copydoc BaseException::BaseException
     */
    explicit ExpiredPointer(const std::string& msg = ""):
        BaseException(msg){};

    virtual ~ExpiredPointer() = default;
};

}
#endif // EXPIREDPOINTER_H
