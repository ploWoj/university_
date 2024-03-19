#include "University.hpp"

const std::vector<std::unique_ptr<Person>>& University::getVector() const {
    return university_;
}

void University::displayBase() {
    for (const auto& person : university_) {
        person->display();
    }
}

void University::addStudent() {
    university_.emplace_back(std::make_unique<Student>());
}

void University::addStudent(std::string name, std::string surname, std::string address, std::string pesel, std::string gender, size_t indexNumber) {
    if (!findByPesel(pesel)) {
        university_.emplace_back(std::make_unique<Student>(name, surname, address, pesel, gender, indexNumber));
    }
}

void University::addEmployee() {
    university_.emplace_back(std::make_unique<Employee>());
}

void University::addEmployee(std::string name, std::string surname, std::string address, std::string pesel, std::string gender, double salary) {
    if (findByPesel(pesel)) {
        university_.emplace_back(std::make_unique<Employee>(name, surname, address, pesel,gender, salary));
    }
}
