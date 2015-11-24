#ifndef INTERFACE_H
#define INTERFACE_H

#include "MyData.h"

#include <string>
#include <exception>

class Interface
{
public:
    virtual MyData func(const std::string &xml) const = 0;
};

class MyException : public std::exception
{
public:
    MyException(const std::string &error) : msg(error) {}
    virtual ~MyException() {}

    virtual const char *what() const throw() {
        return msg.c_str();
    }

    const std::string msg;
};

#endif // INTERFACE_H
