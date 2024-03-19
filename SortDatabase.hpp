#pragma once

#include "Command.hpp"

class SortDatabase : public Command {
public:
    SortDatabase() = default;

    void operator()(University& university) override {
        std::cout <<"......................................................................................\n";
        int option;

        std::array<std::pair<std::string, std::function<void()>>, 4> sortOptions {{
            {"1-sort-by-Pasel", [&](){ university.sortByPesel();
                                        std::cout << "Database sorted by Pasel\n";
                                        return; }},
            {"2-sort-by-Surname", [&](){ university.sortBySurname();
                                        std::cout << "Database sorted by Surname\n";
                                        return; }},
            {"3-sort-by-Salary", [&](){ university.sortBySalary();
                                        std::cout << "Database sorted by Salary\n";
                                        return; }},
            {"4-back-to-main-menu", [&]() { do
                                            {
                                              std::cout << "\nDo you want to back to main-menu ( y/n ):  ";
                                              char c;
                                              std::cin >> c;
                                              if (c == 'n') { option += 1;
                                                                   break; }
                                              if (c == 'y') { break; }
                                            } while (true);
                                            return;
                                            }}
        }};

        while(true) {
            std::cout << "Chose kind of sort to want to do : \n";
            for (const auto& [key, value] : sortOptions) {
                std::cout << key << '\n';
            }
            std::cout << "\nyour choice (number  :) ";
            try
            {
                std::cin >> option;
                auto sort = sortOptions.at(option - 1).second;
                sort();
            }
            catch(...)
            {
                std::cout << "Invalid input\n";
            }

            if (option == sortOptions.size()) {
                break;
            }
            
            if (option == sortOptions.size()) {
                break;
            }
            option = -1;
        }
    }

    void getName() const override {
        std::cout << "SortDatabase\n";
    }

};