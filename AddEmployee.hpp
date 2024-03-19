#pragma once

#include <array>
#include <iostream>
#include <studio.h>
#include <string>

#include "Command.hpp"

class AddEmployee : public Command {
public:
    AddEmployee() = default;

    void operator()(University& university) override {
        this->getName();
        std::cout << "......................................................................................\n";
        std::array<std::string, 6> data{};
        std::array<std::string, 6> data_type{"Name: ", "Surname: ", "Address: ", "Pesel: ", "Gender: ", "Salary: " };
        std::string str;

        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data_type[i] << '\n';
            std::cin >> str;
            data[i] = str;
            str = "";
        }

        university.addEmployee(data[0],data[1],data[2],data[3],data[4],std::stod(data[5]));
        std::cout << "......................................................................................\n";
        std::cout << "Done\n";
        getchar();
    }

    void getName() {
        std::cout << "AddEmployee\n";
    }
}