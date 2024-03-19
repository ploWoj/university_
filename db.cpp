#include "db.hpp"
#include "Command.hpp"
#include "DisplayDatabase.hpp"
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

void Db::printCommands() {
    for (const auto& [key, value] : commands_) {
        std::cout << key << " -> ";
        value->getName();
    }
    std::cout << "\n\nYour choice (sign) : ";
}

void Db::run() {
    init();
    while(dbOn_) {
        std::cout << "========================================================\n";
        std::cout << "==================UNIVERSITY DATABASE===================\n\n";
        std::cout << "MENU: \n";
        
        printCommands();
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
    commands_["1"] = (std::make_unique<DisplayDatabase>());
    commands_["2"] = (std::make_unique<AddStudent>());
    commands_["3"] = (std::make_unique<AddEmployee>());
    commands_["4"] = (std::make_unique<SortDatabase>());
    commands_["5"] = (std::make_unique<Find>());
    commands_["6"] = (std::make_unique<Remove>());
    commands_["7"] = (std::make_unique<ImportExport>());
    commands_["q"] = (std::make_unique<Exit>(dbOn_));
}