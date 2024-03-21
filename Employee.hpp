#pragma once 

#include <string>

#include "Person.hpp"

class Employee : public Person {
private:
    double salary_{0.0};
public:
    Employee() = default;
    Employee(std::string name, std::string surname, std::string address, std::string pesel, std::string gender, double salary);
    Employee(const Person& person, double salary);
    ~Employee() = default;
    void setSalray(const double&);
    double getSalary() const;
    // void display() const override;
    friend std::ostream& operator<<(std::ostream& os, const Employee&);
    friend std::istream& operator>>(std::istream& in, Employee&);        
};