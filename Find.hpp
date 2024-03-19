#pragma once 

#include <array>
#include <functional>
#include <iostream>
#include <stdio.h>


#include "Command.hpp"
#include "Employee.hpp"
#include "Student.hpp"
#include "University.hpp"
#include "Person.hpp"

void printSettings(Person* person) {
    std::array<std::pair<std::string, std::function<void()>>, 5> settings {{
        {"1-change-the-name", [&]() { std::cout << "New name: ";
                                        std::string name;
                                        std::cin >> name;
                                        person->setName(name);
                                        std::cout << "Done\n";
                                        return;}},
        {"2-change-the-surname", [&]() { std::cout << "New surname: ";
                                        std::string surname;
                                        std::cin >> surname;
                                        person->setSurname(surname);
                                        std::cout << "Done\n";
                                        return;}},
        {"3-change-the-address", [&]() { std::cout << "New address: ";
                                        std::string address;
                                        std::cin >> address;
                                        person->setAddress(address);
                                        std::cout << "Done\n";
                                        return;}},
        {"4-change-the-gender", [&]() { std::cout << "New gender: ";
                                        std::string gender;
                                        std::cin >> gender;
                                        person->setGender(gender);
                                        std::cout << "Done\n";
                                        return;}},
        {"5-exit", [&]() {    do {
                            std::cout << "\nDo you want to back ( y/n ): ";
                            char c;
                            std::cin >> c;
                            if (c == 'n'){
                                break;
                            }
                            if (c == 'y') {
                                break; }} while (true);
                            return;}},
    }};

    while (true) {
        std::cout << "\nSettings Options : \n";
        for (const auto& [key, value] : settings) {
            std::cout << key << '\n';
        }
        int option;
        std::cout << "\nyour choice (number) : ";
        try
        {
            std::cin >> option;
            auto find = settings.at(option - 1).second;
            find();
        }
        catch(...)
        {
            std::cout << "Invalid input\n";
        }

        if (option == settings.size()) {
            break;
        }
        option = -1;
        }
}

class Find : public Command {
public:
    Find() = default;

    void operator()(University& university) override {
        std::cout <<"......................................................................................\n";
        int option{};

        std::array<std::pair<std::string, std::function<void()>>, 3> findOptions {{
            {"1-find-by-Pesel", [&]() { std::cout << "Provide PESEL of the person you are looking for: ";
                                        std::string pesel;
                                        // std::getline(std::cin, pesel);
                                        std::cin >> pesel;
                                        auto person = university.findByPesel(pesel);
                                        std::cout <<"......................................................................................\n";
                                        if (person) {
                                            *person->display();
                                            std::cout <<"......................................................................................\n";
                                            printSettings(person);
                                        } else {
                                            std::cout << "There is no person with that pesel\n";
                                        }
                                        std::cout <<"......................................................................................\n";
                                        std::getchar();
                                        return;}},
            {"2-find-by-Surname", [&]() { 
                                        std::cout << "Provide surname of the person you are looking for: ";
                                        std::string surname;
                                        // std::getline(std::cin, surname); 
                                        std::cin >> surname;
                                        auto person = university.findBySurname(surname);
                                        std::cout <<"......................................................................................\n";
                                        if (person) {
                                            person->display();
                                            std::cout <<"......................................................................................\n";
                                            printSettings(person);
                                        } else {
                                            std::cout << "There is on person with that surname\n";
                                        }
                                        std::cout <<"......................................................................................\n";
                                        std::getchar();
                                        return;}},
            {"3-back-to-main-manu", [&](){ do {
                                            std::cout << "\nDo you want to back to main-menu ( y/n ):  ";
                                            char c;
                                            std::cin >> c;
                                            if ( c == 'n') { option += 1;
                                                             break; }
                                            if ( c == 'y') { break; }
                                        } while (true);
                                        return;
                                     }}
        }};

        while(true) {
            std::cout << "Find Options: \n";
            for (const auto& [key, value] : findOptions) {
                std::cout << key << '\n';
            }

            std::cout << "\nyour choice (number) : ";
            try
            {
                std::cin >> option;
                auto find = findOptions.at(option - 1).second;
                find();
            }
            catch(...)
            {
                std::cout << "Invalid input\n";
            }

            if (option == 3) {
                break;
            }
            option = -1;
            
        }
    }

    void getName() const override {
        std::cout << "Find\n";
    }
};