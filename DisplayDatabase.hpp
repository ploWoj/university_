#pragma once

#include <iostream>
#include <stdio.h>

#include "Command.hpp"

class DisplayDatabase : public Command {
public:
    DisplayDatabase() = default;
    
    void operator()(University& university) override {
        std::cout << "......................................................................................\n";
        university.displayBase();
        std::cout << "......................................................................................\n";
        std::getchar();
    }

    void getName() {
        std::cout << "DisplayDatabase\n";
    }
};