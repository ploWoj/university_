#include "Employee.hpp"

#include <utility>

Employee::Employee(const std::string &name,
                   const std::string &surname,
                   const std::string &address,
                   const std::string &pesel,
                   const std::string &gender,
                   double salary)
    : Person(name, surname, address, pesel, gender), salary_(salary) {}

Employee::Employee(std::string &&name,
                   std::string &&surname,
                   std::string &&address,
                   std::string &&pesel,
                   std::string &&gender,
                   double salary)
    : Person(std::move(name), std::move(surname), std::move(address), std::move(pesel), std::move(gender)), salary_(salary) {}

Employee::Employee(const Person &person, double salary) : Person(person), salary_(salary) {}

Employee::Employee(Person &&person, double salary) : Person(std::move(person)), salary_(salary){}

void Employee::setSalray(const double &salary)
{
    salary_ = salary;
}

double Employee::getSalary() const
{
    return salary_;
}

std::ostream &operator<<(std::ostream &os, const Employee &employee)
{
    os << employee.name_ << Person::formatDelimiter
       << employee.surname_ << Person::formatDelimiter
       << employee.address_ << Person::formatDelimiter
       << employee.pesel_ << Person::formatDelimiter
       << employee.gender_ << Person::formatDelimiter
       << employee.salary_ << Person::formatDelimiter;
    return os;
}

std::istream &operator>>(std::istream &in, Employee &employee)
{
    char delim{};
    Person person{};
    double salary{};
    in >> person >> delim >> salary;
    if (delim != ',')
    {
        in.clear(std::ios_base::failbit);
    }
    employee = Employee(person, salary);
    return in;
}