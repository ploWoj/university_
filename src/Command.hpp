#pragma once

#include <array>
#include <functional>
#include <utility>

#include "University.hpp"

class Command {
public:
    Command() = default;
    virtual ~Command() = default;
    virtual void operator()(University& university) = 0;
    virtual void getName() const = 0;
};