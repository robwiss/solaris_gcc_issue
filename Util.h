#ifndef UTIL_H
#define UTIL_H

#include <memory>

template <typename T>
void noop_free(T *ptr)
{
    return;
}

/** Create a shared_ptr with a custom deleter to hold libxml-allocated memory with an appropriate delete function
 *
 */
template <typename T>
std::shared_ptr<T> scoped_cptr(T *ptr, void(*deleter)(T *))
{
    if (nullptr != ptr)
    {
        std::shared_ptr<T> retval(ptr, deleter);
        return retval;
    }
    else
    {
        std::shared_ptr<T> retval(ptr, noop_free<T>);
        return retval;
    }
}

#endif // UTIL_H
