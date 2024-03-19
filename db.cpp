#include "db.hpp"
#include "Command.hpp"
#include "DispalyDatabase.hpp"
#include "AddEmployee.hpp"
#include "AddStudent.hpp"
#include "SortDatabase.hpp"
#include "Find.hpp"
#include "Remove.hpp"
#include "ImportExport.hpp"
#include "Exit.hpp"

#include <iostream>
#include <map>
#include <memory>

void printCommands(std::map<std::string, std::unique_ptr<Command>& commands) {
    for (const auto& [key, value] : commands) {
        std::cout << key << " -> ";
        value->getName();
    }
    std::cout << "\n\nYour choice (sign) : ";
}

void Db::run() {
    init();
    while(dbON_) {
        std::cout << "========================================================\n";
        std::cout << "==================UNIVERSITY DATABASE===================\n\n";
        std::cout << "MENU: \n";
        printCommands(commands_);
        std::string option{};
        std::cin >> option;
        try
        {
            Command& command = *commands_.at(option);
            command(university_);
        }
        catch(...)
        {
            std::cout << "Invalid input\n";
        }
    }
}

void Db::init() {
    dbOn_ = true;
    std::string dbFile("db.txt");
    university_.importDatabase(dbFile);
    commands_["1"] = (std::make_uniqe<DisplayDatabase>());
    commands_["2"] = (std::make_uniqe<AddStudent>());
    commands_["3"] = (std::make_uniqe<AddEmployee>());
    commands_["4"] = (std::make_uniqe<SortDatabase>());
    commands_["5"] = (std::make_uniqe<Find>());
    commands_["6"] = (std::make_uniqe<Remove>());
    commands_["7"] = (std::make_uniqe<ImportExport>())
    commands_["q"] = (std::make_uniqe<Exit>(dbON_))
}