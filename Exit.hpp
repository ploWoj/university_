#pragma once

#include <iostream>

#include "Command.hpp"

class Exit : public Command {
private:
    bool& dbON_;
public:
    Exit(bool& dbON) : dbON_(dbON) {};
    ~Exit() override = default;

    void operator()([[maybe_unused]] University& university) override {
        do
        {
            std::cout << "Do you want to exit ? ( y/n ): ";
            char c;
            std::cin >> c;
            if ( c == 'n') {
                break;
            }
            if (c == 'y') {
                std::string dbFile("db.txt");
                university.exportDatabase(dbFile);
                dbON_ = false;
            }
        } while (true);
    }

    void getName() const override {
        std::cout << "Exit";
    }
};