#ifndef IMPL_H
#define IMPL_H

#include "Interface.h"
#include "MyData.h"

#include <string>

class Impl : public Interface
{
public:
    virtual MyData func(const std::string &xml) const;
};

#endif // IMPL_H
