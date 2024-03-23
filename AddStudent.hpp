#pragma once

#include <array>
#include <iostream>
#include <stdio.h>
#include <string>

#include "Command.hpp"

class AddStudent : public Command {
public:
    AddStudent() = default;

    void operator()(University& university) override {
        this->getName();
        std::cout << "......................................................................................\n";
        std::array<std::string, 6> data{};
        std::array<std::string, 6> data_type{"Name: ", "Surname: ", "Address: ", "Pesel: ", "Gender: ", "IndexNumber: " };
        std::string str;

        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data_type[i] << '\n';
            std::getline(std::cin, str);
            data[i] = str;
            str = "";
        }

        university.addStudent(data[0],data[1],data[2],data[3],data[4],std::stod(data[5]));
        std::cout << "......................................................................................\n";
        std::cout << "Done\n";
        getchar();
    }

    void getName() const override {
        std::cout << "AddStudent\n";
    }
};