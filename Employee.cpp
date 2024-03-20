#include "Employee.hpp"

Employee::Employee(std::string name, std::string surname, std::string address, std::string pesel, std::string gender, double salary)
    : Person(name, surname, address, pesel, gender), salary_(salary) {}

void Employee::setSalray(const double& salary) {
    salary_ = salary;
}

double Employee::getSalary() const {
    return salary_;
}

void Employee::display() const {
    std::cout << name_ << ", " << surname_ << ", " << address_ << ", " <<
    pesel_ << ", " << gender_ << ", " << salary_ << '\n';
}