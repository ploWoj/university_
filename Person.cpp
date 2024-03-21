#include "Person.hpp"

std::string get_string_to_char(std::istream& in, char delimiter) {
    std::string temp{};
    for (char current_char{}; in >> current_char;) {
        if (current_char == delimiter) {
            in.putback(current_char);
            break;
        }

        temp.push_back(current_char);
    }
    return temp;
}

Person::Person(std::string name, std::string surname, std::string address, std::string pesel, std::string gender)
        : name_(name), surname_(surname), address_(address), pesel_(pesel), gender_(gender) {}

void Person::setName(const std::string& name) {
    name_ = name;
}

void Person::setSurname(const std::string& surname) {
    surname_ = surname;
}

void Person::setAddress(const std::string& address) {
    address_ = address;
}

void Person::setPesel(const std::string& pesel) {
    pesel_ = pesel;
}

void Person::setGender(const std::string& gender) {
    gender_ = gender;
}

std::string Person::getName() const { 
    return name_;
}

std::string Person::getSurname() const {
    return surname_;
}

std::string Person::getAddress() const {
    return address_;
}

std::string Person::getPesel() const {
    return pesel_;
}

std::string Person::getGender() const {
    return gender_;
}

void Person::display() const {
    std::cout << name_ << ", " << surname_ << ", " << address_ << ", " <<
        pesel_ << ", " << gender_ << '\n';
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << person.name_ << " " << person.surname_ << " " << person.address_ <<
         person.gender_ << person.gender_;
    return os;
}

 std::istream& operator>>(std::istream& is, Person& person) {

 }