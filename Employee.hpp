#pragma once

#include <string>

#include "Person.hpp"

class Employee : public Person
{
private:
    double salary_{0.0};

public:
    Employee() = default;
    Employee(const std::string &name,
             const std::string &surname,
             const std::string &address,
             const std::string &pesel,
             const std::string &gender,
             double salary);

    Employee(std::string &&name,
             std::string &&surname,
             std::string &&address,
             std::string &&pesel,
             std::string &&gender,
             double salary);

    Employee(const Employee &) = default;
    Employee(Employee &&) = default;

    Employee &operator=(const Employee &) = default;
    Employee &operator=(Employee &&) = default;

    Employee(const Person &person, double salary);
    Employee(Person &&person, double salary);
    ~Employee() = default;

    [[nodiscard]] double getSalary() const;

    void setSalray(const double &);

    friend std::ostream &operator<<(std::ostream &os, const Employee &);
    friend std::istream &operator>>(std::istream &in, Employee &);
};