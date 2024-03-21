#include "Employee.hpp"

Employee::Employee(std::string name, std::string surname, std::string address, std::string pesel, std::string gender, double salary)
    : Person(name, surname, address, pesel, gender), salary_(salary) {}

Employee::Employee(const Person& person, double salary) : Person{person}, salary_(salary) {};

void Employee::setSalray(const double& salary) {
    salary_ = salary;
}

double Employee::getSalary() const {
    return salary_;
}

// void Employee::display() const {
//     std::cout << name_ << ", " << surname_ << ", " << address_ << ", " <<
//     pesel_ << ", " << gender_ << ", " << salary_ << '\n';
// }

std::ostream& operator<<(std::ostream& os, const Employee& employee) {
    os << employee.name_ << Person::formatDelimiter 
       << employee.surname_ << Person::formatDelimiter
       << employee.address_ << Person::formatDelimiter 
       << employee.pesel_ << Person::formatDelimiter
       << employee.gender_ << Person::formatDelimiter
       << employee.salary_ << Person::formatDelimiter;
}
std::istream& operator>>(std::istream& in, Employee& employee) {
    char delim{};
    Person person{};
    double salary{};
    in >> person >> delim >> salary; 
    if (delim != ',') {
        in.clear(std::ios_base::failbit);
    }
    employee = Employee(person, salary);
    return in;
}