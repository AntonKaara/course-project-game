#ifndef RESOURCEERROR_H
#define RESOURCEERROR_H

#include "exceptions/baseexception.h"


namespace Course {

/**
 * @brief The ResourceError class is an Exception-class for
 * errors where an error occurred during resource-processing.
 */
class ResourceError : public BaseException
{
public:
    /**
     * @copydoc BaseException::BaseException
     */
    explicit ResourceError(const std::string& msg = ""):
        BaseException(msg) {}

    /**
     * @copydoc BaseException::~BaseException
     */
    virtual ~ResourceError() = default;

}; // class ResourceError

} // namespace Course


#endif // RESOURCEERROR_H
