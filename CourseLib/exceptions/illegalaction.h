#ifndef ILLEGALACTION_H
#define ILLEGALACTION_H
#include "baseexception.h"

namespace Course {

/**
 * @brief The InvalidPointer exception is usually used in cases, where
 * data can't be accessed through a pointer.
 */
class IllegalAction : public BaseException
{
public:
    /**
     * @copydoc BaseException::BaseException
     */
    explicit IllegalAction(const std::string& msg = ""):
        BaseException(msg){};

    virtual ~IllegalAction() = default;
};

}
#endif // ILLEGALACTION_H
