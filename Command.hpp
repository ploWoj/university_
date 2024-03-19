#pragma once

#include "University.hpp"

class Command {
public:
    Command() = default;
    ~Command() = default;
    virtual void operator()(University& university) = 0;
    virtual void getName() const = 0;
};