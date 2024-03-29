#pragma once


#include <array>
#include <functional>
#include <iostream>
// #include <stdio.h>

#include "Command.hpp"
#include "University.hpp"

class MysqlDb : public Command {
public:
    MysqlDb() = default;

    void operator()(University& university) override {
        std::cout <<"......................................................................................\n";
        size_t option;
        std::array<std::pair<std::string, std::function<void()>>, 3> mysqlOptoins {{
            {"1-Import-from-Mysql", [&]() { std::cout << "IMPORT : Give database name : ";
                                       std::string database;
                                       std::cin >> database;
                                       university.importMysql(database);
                                       return;}},
            {"2-Export-to-Mysql", [&]() { std::cout << " EXPORT : Give database name : ";
                                       std::string database;
                                       std::cin >> database;
                                       do{
                                            std::cout << "If you continue, you will erase current database ( y/n ): \n";
                                            char c;
                                            std::cin >> c;
                                            if (c == 'n') {
                                                option += 1;
                                                break;
                                            }
                                            if (c == 'y') { break; }
                                        } while (true);
                                       university.exportMysql(database);
                                       return; }},
            {"3-back-to-main-manu", [&]() { do
                                                {
                                                    std::cout << "Do you want back to main-menu ( y/n ): \n";
                                                    char c;
                                                    std::cin >> c;
                                                    if (c == 'n') {
                                                        option += 1;
                                                        break;
                                                    }
                                                    if (c == 'y') { break; }
                                                } while (true);
                                                return;
                                        }}
        }};

        while(true) {
            std::cout << "Import from Mysql / Export to Mysql Options : \n";
            for (const auto& [key,value] : mysqlOptoins) {
                std::cout << key << '\n';
            }

            std::cout << "\nyour chocie (number) : ";
            try
            {
                std::cin >> option;
                auto find = mysqlOptoins.at(option - 1).second;
                find();
            }
            catch(...)
            {
                std::cout << "Invalid input \n";
            }

            if (option == mysqlOptoins.size()) {
                break;
            }

            option = -1;
        }
    }

    void getName() const override {
        std::cout << "Import from/ Export to Msql\n";
    }

};
