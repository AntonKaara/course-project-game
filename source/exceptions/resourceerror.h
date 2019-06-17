#ifndef RESOURCEERROR_H
#define RESOURCEERROR_H

#include "../BGBase/source/exceptions/baseexception.h"

namespace Course {

/**
 * @brief The ResourceError class is an Exception-class for cases where
 * an error occurred during resource-processing.
 */
class ResourceError : public BGBase::BaseException
{
public:
    /**
     * @copydoc BGBase::BaseException::BaseException
     */
    explicit ResourceError(const std::string& msg = ""):
        BGBase::BaseException(msg);
    virtual ~ResourceError() = default;
};

}
#endif // RESOURCEERROR_H
