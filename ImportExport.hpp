#pragma once

#include <iostream>
#include <stdio.h>

#include "Command.hpp"
#include "University.hpp"

class ImportExport : public Command {
public:
    ImportExport() = default;

    void operator()(University& university) override {
        std::cout <<"......................................................................................\n";
        int option;
        std::array<std::pair<std::string, std::function<void()>>, 3> impExpOptions {{
            {"1-Import-Database", [&](){ std::cout << "IMPORT : Give file name : ";
                                        std::string fileName;
                                        std::cin >> fileName;
                                        university.importDatabase(fileName);
                                        return; }},
            {"2-Export-Database", [&](){ std::cout << "Export : Give file name : ";
                                        std::string fileName;
                                        std::cin >> fileName;
                                        university.exportDatabase(fileName);
                                        return; }},
            {"3-back-to-main-menu", [&](){do
                                        {
                                            std::cout << "Do you want to back to main-manu ( y/n ): ";
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

        while (true) {
            std::cout << "Import/Export Options : \n";
            for (const auto& [key, value] : impExpOptions) {
                std::cout << key << '\n';
            }

            std::cout << "\nyour choice (number) : ";
            try
            {
                std::cin >> option;
                auto find = impExpOptions.at(option - 1).second;
                find();
            }
            catch(...)
            {
                std::cout << "Invalid input" << '\n';
            }

            if (option == impExpOptions.size()) {
                break;
            }
            option = -1;
        }
    }

    void getName() const override {
        std::cout << "ReadTo/LoadFromFile\n";
    }
};