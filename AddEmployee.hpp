#pragma once

#include <array>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

#include "Command.hpp"

class AddEmployee : public Command {
public:
    AddEmployee() = default;

    void operator()(University& university) override {
        this->getName();
        std::cout << "......................................................................................\n";
        std::array<std::string, 6> data;
        std::array<std::string, 6> data_type{"Name: ", "Surname: ", "Address: ", "Pesel: ", "Gender: ", "Salary: " };
        std::string str;

        for (size_t i = 0; i < data_type.size(); ++i) {
            std::cout << data_type[i] << '\n';
            std::cin >> str;
            data[i] = str;
            str.clear();
        }
        
        try
        {
            university.addEmployee(data[0], data[1], data[2], data[3], data[4], std::stod(data[5]));;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        std::cout << "......................................................................................\n";
        std::cout << "Done\n";
        getchar();
    }

    void getName() const override {
        std::cout << "AddEmployee\n";
    }
};