#pragma once

#include <iostream>

#include "Command.hpp"

class Exit : public Command {
private:
    bool& dbON_;
public:
    Exit(bool& dbON) : dbON_(dbON) {};
    ~Exit() = default;

    void operator()([[maybe_unused]] University& university) override {
        do
        {
            std::cout << "Do you want to exit ? ( y/n ): ";
            char c;
            std::cin >> c;
            if (c == 'n') {
                dbON_ = true;
                return;
            }
            if (c == 'y') {
                std::string dbFile("db.txt");
                university.exportDatabase(dbFile);
                dbON_ = false;
                break;
            }
        } while (true);
    }

    void getName() const override {
        std::cout << "Exit";
    }
};