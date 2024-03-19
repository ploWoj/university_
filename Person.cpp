#include "Person.hpp"

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
        pesel_ << ", " << gender << '\n';
}