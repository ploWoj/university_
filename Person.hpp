#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

namespace Pesel {
    constexpr auto peselSize = 11u;
    bool validatePesel(const std::string&);
}

class Person {
    protected:
        std::string name_ = "";       
        std::string surname_ = "";
        std::string address_ = "";
        std::string pesel_ = "";
        std::string gender_ = "";
    public:
        static constexpr char formatDelimiter{','};

        Person() = default;
        Person(const std::string& name, 
               const std::string& surname, 
               const std::string& address, 
               const std::string& pesel, 
               const std::string& gender);

        Person(std::string&& name, 
               std::string&& surname, 
               std::string&& address, 
               std::string&& pesel, 
               std::string&& gender);

        Person(const Person&) = default;
        Person(Person&&) = default;

        Person& operator=(const Person&) = default;
        Person& operator=(Person&&) = default;
        
        virtual ~Person() = default;

        void setName(const std::string&);
        void setSurname(const std::string&);
        void setAddress(const std::string&);
        void setPesel(const std::string&);
        void setGender(const std::string&);

        [[nodiscard]] std::string getName() const;
        [[nodiscard]] std::string getSurname() const;
        [[nodiscard]] std::string getAddress() const;
        [[nodiscard]] std::string getPesel() const;
        [[nodiscard]] std::string getGender() const;

        friend std::ostream& operator<<(std::ostream& os, const Person&);
        friend std::istream& operator>>(std::istream& is, Person&);

        bool operator==(const Person& person) const;
};

std::string getStringToChar(std::istream&, char delimeter);
