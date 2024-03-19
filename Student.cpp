#include "Student.hpp"

Student::Student(std::string name, std::string surname, std::string address, std::string pesel, std::string gender, size_t indexNumber) 
    : Person(name, surname, address, pesel, gender), indexNumber_(indexNumber) {}

void Student::setIndex(size_t indexNumber) {
    indexNumber_ = indexNumber;
}

size_t Student::getIndex() const {
    return indexNumber_;
}

void Student::display() const override {
    std::cout << name_ << ", " << surname_ << ", " << address_ << ", " << pesel_ << ", " <<
    pesel_ << ", " << gender_ << ", " indexNumber_ << '\n';
}