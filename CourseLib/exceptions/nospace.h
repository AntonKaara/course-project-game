#ifndef NOSPACE_H
#define NOSPACE_H

#include "exceptions/baseexception.h"


namespace Course {

/**
 * @brief The NoSpace class is an Exception-class for
 * errors where GameObjects are being placed onto Tiles with no space available.
 */
class NoSpace : public BaseException
{
public:
    /**
     * @copydoc BaseException::BaseException
     */
    explicit NoSpace(const std::string& msg = ""):
        BaseException(msg) {}

    /**
     * @copydoc BaseException::~BaseException
     */
    virtual ~NoSpace() = default;

}; // class NoSpace

} // namespace Course


#endif // NOSPACE_H
