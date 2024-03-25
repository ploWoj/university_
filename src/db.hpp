#pragma once

#include "Command.hpp"
#include "University.hpp"

#include <map>

class Db {
private:
    bool dbOn_{};
    std::map<std::string, std::unique_ptr<Command>> commands_{};
    University university_{};
    void printCommands();
public:
    Db() = default;
    void run();
    void init();
};