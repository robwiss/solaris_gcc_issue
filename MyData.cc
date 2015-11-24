#include "MyData.h"

void MyData::addDescription(const std::string &desc)
{
    _descriptions.push_back(desc);
}

const std::vector<std::string> &MyData::getDescriptions() const
{
    return _descriptions;
}
