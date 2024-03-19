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

Person* University::findBySurname(const std::string& surname) {
    auto isTheSame = [&surname](std::unique_ptr<Person>& person) {
        return person->getSurname() == surname;
    };
    auto it = std::find_if(university_.begin(), university_.end(), isTheSame);

    if (it == university_.end()) {
        return nullptr;
    }

    Person* person_ptr = it->get();

    return person_ptr;
}

Person* University::findByPesel(const std::string& pesel) {
    auto isTheSame = [&pesel](std::unique_ptr<Person>& person) {
        return person->getPesel();
    };

    auto it = std::find_if(university_.begin(), university_.end(), isTheSame);

    if (it == university_.end()) {
        return nullptr;
    }

    Person* person_ptr = it->get();
    return person_ptr;
}

void University::sortByPesel() {
    std::sort(university_.begin(), university_.end(),
                [](const std::unique_ptr<Person>& lhs, const std::unique_ptr<Person>& rhs) {
                    return lhs->getPesel() > rhs->getPesel();
                });
}

void University::sortBySurname() {
    std::sort(university_.begin(), university_.end(),
                [](const std::unique_ptr<Person>& lhs, const std::unique_ptr<Person>& rhs) {
                    return lhs->getSurname() < rhs->getSurname();
                })
}