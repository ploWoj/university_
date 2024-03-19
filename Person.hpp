#pragma once

#include <algorithm>
#include <iostream>
#include <memeory>
#include <string>
#include <vector>

class Person {
    protected:
        std::string name_ = "";       
        std::string surname_ = "";
        std::string address_ = "";
        std::string pesel_ = "";
        std::string gender_ = "";
    public:
        Person() = default;
        ~Person() = default;
        Person(std::string name, std::string surname, std::string address, std::string pesel, std::string gender);

        void setName(const std::string&);
        void setSurname(const std::string&);
        void setAddress(const std::string&);
        void setPesel(const std::string&);
        void setGender(const std::string&);

        std::string getName() const;
        std::string getSurname() const;
        std::string getAddress() const;
        std::string getPesel() const;
        std::string getGender() const;

        virtual void display() = 0;
};
