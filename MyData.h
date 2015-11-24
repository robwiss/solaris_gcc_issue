#ifndef MYDATA_H
#define MYDATA_H

#include <vector>
#include <string>

struct MyData
{
    void addDescription(const std::string &desc);

    const std::vector<std::string> &getDescriptions() const;
private:
    std::vector<std::string> _descriptions;
};

#endif // MYDATA_H
